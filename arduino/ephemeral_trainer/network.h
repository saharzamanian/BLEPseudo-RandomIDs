#ifndef NETWORK_H
#define NETWORK_H


struct Neuron {
	int numInput;
	float* W;
	float B;
	float X;
	// For back propagation, convention, dA means dL/dA or partial derivative of Loss over Accumulative output
	float* dW;
	float dA;
	float dB;
};

struct Layer {
	int numNeuron;
	Neuron* Neu;
};


void initNN();

void train();

void printAccuracy();


#endif
