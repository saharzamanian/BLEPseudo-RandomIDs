#include<TinyMLShield.h>
#include "network.h" 


const String incoming_data[11] = {
  "b1ee6d97ff37bba0f246a816bf2f55b1a636c14454e5891b0b3b297d5b2fa5d",
  "6b31ad7d9f1badf1bd21bebe35d9ad6c341c166c1647ba13cba47447df379f",
  "d187c056abf26d8726918c67954e1442af13d93e1f77474c9891805d70cc72",
  "b9982233c82619262a97663192e1f6d3291dd98a2ff8e973971946a855ddc7",
  "2a785999d9f48cbaaeea8916159fc35107a61ea8b95fdf46d4ad45309d2969",
  "aa5034629f44d7f0714b83c4f3e8f2451cf0cc56fcfbc66d476296f541e9b3a6",
  "d2aa959dec6cacdc3988c61e538db3549c61895ca94177517e60dfef2cf8e61c",
  "a0d589ae532d176286d2e3c15a8e66cf7a8b5dbff7864c7c824bf7225b966",
  "3dedfc1a93f98c956f63c780d394d7f2347e42062a49ef9fe4ed58e3bcb61",
  "229ee78cd1f9c54253ecc1f6b2cb736f884e68dbb2bf587e622bf4f48a9b38",
  "c7a5b22c1b42c75ab53ef487656c7ea1271fb3fea0ddeeacd7bceb4c555e3e"
};


const int incoming_labels[11] = {
  1, 0, 0, 3, 1, 1, 3, 2, 2, 2, 3
};


void initRandomizer(int seed = 0) {
  srand(seed);
}


void initSerialInterface() {
  Serial.begin(9600); 
  while (!Serial);
}


void setup() {   
  initRandomizer();

  initSerialInterface();

  initializeShield();

  initNN();

  Serial.println("The accuracy before training");
  printAccuracy();
}


void loop() {
  bool performPrediction = true;
  static unsigned int incomingItem = 0;
  
  bool trigger = readShieldButton();
  
  if (trigger) {  
    if (performPrediction) {
      predict(incoming_data[incomingItem], incoming_labels[incomingItem]);
      ++incomingItem;
    }      
    else {
      train(); 
      printAccuracy();   
    }
  }
}
