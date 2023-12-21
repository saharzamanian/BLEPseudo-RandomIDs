#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<TinyMLShield.h>

#include "data.h"
#include "nn.h" 


#define PRINT_WEIGTHS 0

          
void do_training() {
#if PRINT_WEIGTHS      
  Serial.println("Now Training");
  PRINT_WEIGHTS();
#endif

  static int epoch_count = 0;
  Serial.print("Epoch count (training count): ");
  Serial.print(++epoch_count);
  Serial.println();

  // reordering the index for more randomness and faster learning
  shuffleIndx();
  
  // starting forward + Backward propagation
  for (int j = 0; j < NUM_TRAINING_DATA; j++) {
    generateTrainVectors(j);  
    forwardProp();
    backwardProp();
  }

  Serial.println("Accuracy after local training:");
  printAccuracy();

}


void initRandomizer(int seed = 0) {
  srand(seed);
}


void initSerialInterface() {
  Serial.begin(9600); 
  while (!Serial);
}


void initNN() {
  int weights_bias_cnt = calcTotalWeightsBias(); 

  Serial.print("The total number of weights and bias used for on-device training on Arduino: ");
  Serial.println(weights_bias_cnt);

  // Allocate common weight vector, and pass to setupNN, setupBLE
  DATA_TYPE* WeightBiasPtr = (DATA_TYPE*) calloc(weights_bias_cnt, sizeof(DATA_TYPE));

  setupNN(WeightBiasPtr);  // CREATES THE NETWORK BASED ON NN_def[]
}


void setup() {   
  initRandomizer();

  initSerialInterface();

  initializeShield();

  initNN();

  Serial.print("The accuracy before training");
  printAccuracy();
  
  Serial.println("Use the on-shield button to start and stop the loop code ");
}


void loop() {
  bool retrain_requested = readShieldButton();
  
  if (retrain_requested) {    
    Serial.println("Start training");
    do_training();    
  }
}
