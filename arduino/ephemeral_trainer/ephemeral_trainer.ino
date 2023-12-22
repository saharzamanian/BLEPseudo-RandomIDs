#include<TinyMLShield.h>
#include "network.h" 


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
  bool retrain_requested = readShieldButton();
  
  if (retrain_requested) {        
    train();    
  }
}
