#include <ArduinoBLE.h>
#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

#include "net.h" // network weights

#define N_INPUTS 64
#define N_OUTPUTS 7
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
       }
    }
    
    Serial.println("* Disconnected to central - sender device!");
  }

  delay(1000);
}


void run_cnn() {
    float my_test[64];
    float my_pred[7] = {0};

    char aa[2] = {0, 0};

    for (int i = 0; i < 64; ++i) {
        aa[0] = values[i];
        Serial.print(strtol(aa, 0, 16));
    }

    //uint32_t start = micros();
    tf.predict(my_test, my_pred);
    //uint32_t timeit = micros() - start;
    Serial.println(tf.probaToClass(my_pred));

    
    
    delay(2000);
}