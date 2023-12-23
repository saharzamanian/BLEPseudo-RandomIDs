#ifndef NETWORK_H
#define NETWORK_H


struct Neuron {
	int numInputs;
	float* W;
	float B;
	float X;
	// For back propagation, convention, dA means dL/dA or partial derivative of Loss over Accumulative output
	float* dW;
	float dA;
	float dB;
};

struct Layer {
	int numNeurons;
	Neuron* neuron;
};


void initNN();

void train();

void printAccuracy();


#endif
