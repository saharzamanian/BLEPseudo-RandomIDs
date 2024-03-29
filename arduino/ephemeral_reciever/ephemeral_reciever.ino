#include <ArduinoBLE.h>
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

#include "net.h" // network weights

#define N_INPUTS 64
#define N_OUTPUTS 4
#define TENSOR_ARENA_SIZE 30 * 1024

Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int receivedEphemeralID = -1;

byte values[65];

BLEService ephemeralService(deviceServiceUuid); 
BLECharacteristic ephemeralCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite, 64);


void setup() {
  Serial.begin(9600);
  while (!Serial);  

  startBLE();
  setupBLE();  

  tf.begin(model);
}

void startBLE() {
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
}

void setupBLE() {  
  Serial.println("Setting up peripheral - receiver");
  Serial.println(" ");
  
  BLE.setLocalName("peripheral - receiver");
  BLE.setAdvertisedService(ephemeralService);
  ephemeralService.addCharacteristic(ephemeralCharacteristic);
  BLE.addService(ephemeralService);
  ephemeralCharacteristic.writeValue(values, 64);
  BLE.advertise();  
}

void loop() {
  Serial.println("- Discovering central - sender device..."); 
  
  BLEDevice central = BLE.central();
  if (central) {
    Serial.println("* Connected to central - sender device!");
    
    while (central.connected()) {
      if (ephemeralCharacteristic.written()) {
         ephemeralCharacteristic.readValue(values, 64);
         Serial.println("received: " + String((char *)values));
         run_cnn();
         Serial.println("");
         //delay(2000);
       }
    }
    
    Serial.println("* Disconnected to central - sender device!");
  }

  delay(1000);
}


float my_test[64];
float my_pred[7] = {0};

void run_cnn() {
    to_float_array();
    //print_float_array();
    
    //uint32_t start = micros();
    tf.predict(my_test, my_pred);
    //uint32_t timeit = micros() - start;
    Serial.print("Predicted label is: ");
    Serial.println(tf.probaToClass(my_pred));
}


void to_float_array() {
    char hex_num[2] = {0, 0};

    for (int i = 0; i < 64; ++i) {
        hex_num[0] = values[i];
        my_test[i] = strtol(hex_num, 0, 16);
    }
}


void print_float_array() {
    for (int i = 0; i < 64; ++i) {
        Serial.print(String(my_test[i]));
        Serial.print(" ");
    }
    Serial.println("");    
}
