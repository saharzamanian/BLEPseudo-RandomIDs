#include "network.h"
#include "ephemeral_data.h"


const float LEARNING_RATE = 0.1;
const float EXP_LIMIT = 78.0;  // limit 88.xx but we need to factor in accumulation for softmax


extern const size_t NUM_INPUT_DATA_ELEMENTS;
const size_t NUM_1ST_LAYER_NEURONS = NUM_INPUT_DATA_ELEMENTS;
const size_t NUM_2ND_LAYER_NEURONS = 30;
const size_t NUM_OUTPUT_NEURONS = 4;

static const unsigned int NUM_LAYER_NEURONS[] = {NUM_1ST_LAYER_NEURONS, NUM_2ND_LAYER_NEURONS, NUM_OUTPUT_NEURONS};
static const size_t NUM_LAYERS = sizeof(NUM_LAYER_NEURONS) / sizeof(NUM_LAYER_NEURONS[0]);


static byte sha256Bytes[NUM_1ST_LAYER_NEURONS+1];
static float input[NUM_1ST_LAYER_NEURONS];
static float hat_y[NUM_OUTPUT_NEURONS];    // target output
static float y[NUM_OUTPUT_NEURONS];        // output after forward propagation

static int inputShuffler[NUM_TRAINING_DATA];

static Layer* g_layers = NULL;

static float* g_weights_biases_buffer = NULL;


inline float fRand() { return (rand() * (1.0/RAND_MAX) - 0.5) * 2; }

inline float relu(float a) { return max(a, 0); }


void initNN() {
  allocateParameters();
  createNetwork();
  deshuffleInput();
}


void allocateParameters() {
  int weights_biases_count = getTotalNumberOfParameters(); 
  g_weights_biases_buffer = (float*) calloc(weights_biases_count, sizeof(float));
  Serial.print("The total number of weights and biases used for on-device training: ");
  Serial.println(weights_biases_count);  
}


int getTotalNumberOfParameters()
{
	int count = 0;
	for (unsigned int i = 0; i < NUM_LAYERS - 1; i++) {
    int num_layer_weights = NUM_LAYER_NEURONS[i] * NUM_LAYER_NEURONS[i + 1];
    int num_layers_biases = NUM_LAYER_NEURONS[i + 1];
		count += num_layer_weights + num_layers_biases;
	}

	return count;
}


void createNetwork() {
	g_layers = (Layer*)calloc(NUM_LAYERS, sizeof(Layer));

	// First layer has no input weights
	g_layers[0] = createLayer(NUM_LAYER_NEURONS[0]);

	for (unsigned int i = 1; i < NUM_LAYERS; i++) {
		g_layers[i] = createLayer(NUM_LAYER_NEURONS[i]);
		for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i]; j++) {
			g_layers[i].neuron[j] = createNeuron(NUM_LAYER_NEURONS[i - 1]);
		}
	}
}


Neuron createNeuron(int numInputs) {
	Neuron neuron;
  neuron.numInputs = numInputs;
	neuron.B = fRand();	
	neuron.W = (float*)calloc(numInputs, sizeof(float));
	neuron.dW = (float*)calloc(numInputs, sizeof(float));
	for (int i = 0; i < numInputs; i++) {
		neuron.W[i] = fRand();
		neuron.dW[i] = 0.0;
	}
	neuron.dA = 0.0;
	neuron.dB = 0.0;

	return neuron;
}


Layer createLayer(int numNeurons) {
	Layer layer;
	layer.numNeurons = numNeurons;
	layer.neuron = (Neuron*)calloc(numNeurons, sizeof(Neuron));
	return layer;
}


void train() {
  static int epoch_count = 0;
  Serial.print("Training epoch: ");
  Serial.print(++epoch_count);
  Serial.println();

  shuffleInput();
  
  for (int j = 0; j < NUM_TRAINING_DATA; j++) {
    generateTrainVectors(j);  
    forwardPropagation();
    backwardPropagation();
  }
}


float AccFunction (unsigned int layerIndx, int nodeIndx) {
  float accum = 0;
	for (int k = 0; k < NUM_LAYER_NEURONS[layerIndx - 1]; k++) {
    // updating weights/bais and resetting gradient value if non-zero
    if (g_layers[layerIndx].neuron[nodeIndx].dW[k] != 0.0 ) {
      g_layers[layerIndx].neuron[nodeIndx].W[k] += g_layers[layerIndx].neuron[nodeIndx].dW[k];
      g_layers[layerIndx].neuron[nodeIndx].dW[k] = 0.0;
    }
    accum += g_layers[layerIndx].neuron[nodeIndx].W[k] * g_layers[layerIndx - 1].neuron[k].X;
	}

	if (g_layers[layerIndx].neuron[nodeIndx].dB != 0.0 ) {
		g_layers[layerIndx].neuron[nodeIndx].B += g_layers[layerIndx].neuron[nodeIndx].dB;
		g_layers[layerIndx].neuron[nodeIndx].dB = 0.0;
	}
	accum += g_layers[layerIndx].neuron[nodeIndx].B;

	return accum;
}


// this function is to calculate dA
float dLossCalc( unsigned int layerIndx, unsigned int nodeIndx) {
	float Sum = 0;
	// int outputSize = NUM_LAYER_NEURONS[NUM_LAYERS - 1];
	// for the last layer, we use complex computation
	if (layerIndx == NUM_LAYERS - 1) {	
		Sum = y[nodeIndx] - hat_y[nodeIndx];										// Equation (17)
	// for all except last layer, we use simple aggregate of dA
	} else if (AccFunction(layerIndx, nodeIndx) > 0)  {   							
		for (unsigned int i = 0; i < NUM_LAYER_NEURONS[layerIndx + 1]; i++) {
			Sum += g_layers[layerIndx + 1].neuron[i].dA * g_layers[layerIndx + 1].neuron[i].W[nodeIndx]; 	// Equation (24)
		}
	} else {   																		// refer to "Neat Trick" and Equation (21)
		Sum = 0;
	}

	return Sum;
}


void forwardPropagation() {
	float Fsum = 0;
	int maxIndx = 0;
	// Propagating through network
	for (unsigned int i = 0; i < NUM_LAYERS; i++) {
		// assigning node values straight from input for first layer
		if (i == 0) {
			for (unsigned int j = 0; j < NUM_LAYER_NEURONS[0];j++) {
				g_layers[i].neuron[j].X = input[j];
			}
		} else if (i == NUM_LAYERS - 1) {
      // softmax functionality but require normalizing performed later
			for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i];j++) {
				y[j] = AccFunction(i,j);
				// tracking the max index
				if ( ( j > 0 ) && (abs(y[maxIndx]) < abs(y[j])) ) {
					maxIndx = j;
				}
			}
		} else {	
			// for subsequent layers, we need to perform RELU
			for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i];j++) {
				g_layers[i].neuron[j].X = relu(AccFunction(i,j));				// Equation (21)	
			}	
		}
	}

  // performing exp but ensuring we dont exceed 709 or 88 in any terms 
	float norm = abs(y[maxIndx]);
	if (norm > EXP_LIMIT) {
		norm = norm / EXP_LIMIT;
	} else {
		norm = 1.0;
	}

	for (unsigned int j = 0; j < NUM_LAYER_NEURONS[NUM_LAYERS-1]; j++) {
		y[j] = expl(y[j]/norm);
		Fsum += y[j];
	}

  // final normalizing for softmax
	for (unsigned int j = 0; j < NUM_LAYER_NEURONS[NUM_LAYERS-1]; j++) {
		y[j] = y[j]/Fsum;
	}
}


void backwardPropagation() {
	for (unsigned int i = NUM_LAYERS - 1; i > 1; i--) {
    // tracing each node in the layer.
		for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i]; j++) {
		// first checking if drivative of activation function is 0 or not! NEED TO UPGRADE TO ALLOW ACTIVATION FUNCTION OTHER THAN RELU
		g_layers[i].neuron[j].dA = dLossCalc(i, j);

		for (int k = 0; k < NUM_LAYER_NEURONS[i - 1]; k++) {
			g_layers[i].neuron[j].dW[k] = -LEARNING_RATE * g_layers[i].neuron[j].dA * g_layers[i - 1].neuron[k].X;
		}
		g_layers[i].neuron[j].dB = -LEARNING_RATE * g_layers[i].neuron[j].dA;
    }
  }
}


void sha256BytesToFloatArray() {
    char hex_num[2] = {0, 0};
    for (int i = 0; i < NUM_1ST_LAYER_NEURONS; ++i) {
        hex_num[0] = sha256Bytes[i];
        input[i] = strtol(hex_num, 0, 16);
    }
}


void generateTrainVectors(int indx) {
	for (unsigned int j = 0; j < NUM_OUTPUT_NEURONS; j++) {
		hat_y[j] = 0.0;
	}
	hat_y[ train_labels[inputShuffler[indx]] ] = 1.0;
  
  train_data[inputShuffler[indx]].getBytes(sha256Bytes, NUM_1ST_LAYER_NEURONS+1);
	sha256BytesToFloatArray();
}


void shuffleInput()
{
  for (unsigned int i = 0; i < NUM_TRAINING_DATA - 1; i++)
  {
    size_t j = i + rand() / (RAND_MAX / (NUM_TRAINING_DATA - i) + 1);
    unsigned int t = inputShuffler[j];
    inputShuffler[j] = inputShuffler[i];
    inputShuffler[i] = t;
  }
}


void deshuffleInput()
{
	for (unsigned int i = 0; i < NUM_TRAINING_DATA; i++) {
		inputShuffler[i] = i;
	}
}


void printAccuracy()
{
  // checking accuracy if training data
  int correctCount = 0;

  for (unsigned int i = 0; i < NUM_TRAINING_DATA; i++) {
    int maxIndx = 0;
   
    train_data[i].getBytes(sha256Bytes, NUM_1ST_LAYER_NEURONS+1);
	  sha256BytesToFloatArray();

    forwardPropagation();
    for (unsigned int j = 1; j < NUM_OUTPUT_NEURONS; j++) {
      if (y[maxIndx] < y[j]) {
        maxIndx = j;
      }
    }
    if (maxIndx == train_labels[i]) {
      correctCount += 1;
    }
  }

  float Accuracy = correctCount * 1.0 / NUM_TRAINING_DATA;
  Serial.print("Training Accuracy: ");
  Serial.println(Accuracy);

  correctCount = 0;
  for (unsigned int i = 0; i < NUM_VALIDATION_DATA; i++) {
    int maxIndx = 0;
    
    validation_data[i].getBytes(sha256Bytes, NUM_1ST_LAYER_NEURONS+1);
	  sha256BytesToFloatArray();

    forwardPropagation();
    for (unsigned int j = 1; j < NUM_OUTPUT_NEURONS; j++) {
      if (y[maxIndx] < y[j]) {
        maxIndx = j;
      }
    }
    if (maxIndx == validation_labels[i]) {
      correctCount += 1;
    }
  }

  Accuracy = correctCount * 1.0 / NUM_VALIDATION_DATA;
  Serial.print("Validation Accuracy: ");
  Serial.println(Accuracy);

  correctCount = 0;
  for (unsigned int i = 0; i < NUM_TEST_DATA; i++) {
    int maxIndx = 0;

    test_data[i].getBytes(sha256Bytes, NUM_1ST_LAYER_NEURONS+1);
	  sha256BytesToFloatArray();

    forwardPropagation();
    for (unsigned int j = 1; j < NUM_OUTPUT_NEURONS; j++) {
      if (y[maxIndx] < y[j]) {
        maxIndx = j;
      }
    }
    if (maxIndx == test_labels[i]) {
      correctCount += 1;
    }
  }

  Accuracy = correctCount * 1.0 / NUM_TEST_DATA;
  Serial.print("Test Accuracy: ");
  Serial.println(Accuracy);
  Serial.println("");
}


#define PACK 0
#define UNPACK 1
#define AVERAGE 2
// 0 -> pack vector for creating vector based on local NN for bluetooth transmission
// 1 -> unpack vector for updating weights on local NN after receiving vector via bluetooth transmission
// 2 -> average between values in pointer and location network values, and update both local NN and pointer value
void packUnpackVector(int Type)
{
  unsigned int ptrCount = 0;
  if (Type == PACK) {
    // Propagating through network, we store all weights first and then bias.
    // we start with left most layer, and top most node or lowest to highest index
    for (unsigned int i = 1; i < NUM_LAYERS; i++) {
      for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i]; j++) {
        for (unsigned int k = 0; k < g_layers[i].neuron[j].numInputs; k++) {
          g_weights_biases_buffer[ptrCount] = g_layers[i].neuron[j].W[k];
          ptrCount += 1;
        }
        g_weights_biases_buffer[ptrCount] = g_layers[i].neuron[j].B;
        ptrCount += 1;
      }
    }
    //Serial.print("Total count when packing:");
    //Serial.println(ptrCount);
  } else if (Type == UNPACK) {
    // Propagating through network, we store all weights first and then bias.
    // we start with left most layer, and top most node or lowest to highest index
    for (unsigned int i = 1; i < NUM_LAYERS; i++) {
      for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i]; j++) {
        for (unsigned int k = 0; k < g_layers[i].neuron[j].numInputs; k++) {
          g_layers[i].neuron[j].W[k] = g_weights_biases_buffer[ptrCount];
          ptrCount += 1;
        }
        g_layers[i].neuron[j].B = g_weights_biases_buffer[ptrCount];
        ptrCount += 1;
      }
    }
  } else if (Type == AVERAGE) {
    // Propagating through network, we store all weights first and then bias.
    // we start with left most layer, and top most node or lowest to highest index
    for (unsigned int i = 1; i < NUM_LAYERS; i++) {
      for (unsigned int j = 0; j < NUM_LAYER_NEURONS[i]; j++) {
        for (unsigned int k = 0; k < g_layers[i].neuron[j].numInputs; k++) {
          g_layers[i].neuron[j].W[k] = (g_weights_biases_buffer[ptrCount] + g_layers[i].neuron[j].W[k] ) / 2;
          g_weights_biases_buffer[ptrCount] = g_layers[i].neuron[j].W[k];
          ptrCount += 1;
        }
        g_layers[i].neuron[j].B = (g_weights_biases_buffer[ptrCount] + g_layers[i].neuron[j].B ) / 2;
        g_weights_biases_buffer[ptrCount] = g_layers[i].neuron[j].B;
        ptrCount += 1;
      }
    }
  }
}
