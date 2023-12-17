#include <Crypto.h>
#include <SHA256.h>
#include <ArduinoBLE.h>

#define NUM_HASH_BYTES 32

const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

BLEDevice peripheral;

String deviceSeed = "Device0";


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  unsigned long seed = 1;
  randomSeed(seed);

  startBLE();
  setupBLE();
}


void startBLE() {
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }
}


void setupBLE() {  
  Serial.println("Setting up central - sender");
  Serial.println(" ");  
  
  BLE.setLocalName("central - sender"); 
  BLE.advertise(); 
}


void loop() {
  connectToPeripheral();
  controlPeripheral();
}


BLEDevice connectToPeripheral() {
  Serial.println("- Discovering peripheral - receiver device...");
  
  do
  {
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();
  } while (!peripheral);
  
  Serial.println("* Peripheral - receiver device found!");
  Serial.print("* Device name: ");
  Serial.println(peripheral.localName());
  Serial.print("* Advertised service UUID: ");
  Serial.println(peripheral.advertisedServiceUuid());
  Serial.println(" ");
  BLE.stopScan(); 
}


void controlPeripheral() {
  Serial.println("- Connecting to peripheral - receiver device...");

  if (peripheral.connect()) {
    Serial.println("* Connected to peripheral - receiver device!");
    Serial.println(" ");
  } else {
    Serial.println("* Connection to peripheral - receiver device failed!");
    Serial.println(" ");
    return;
  }

  Serial.println("- Discovering peripheral - receiver device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("* Peripheral - receiver device attributes discovered!");
    Serial.println(" ");
  } else {
    Serial.println("* Peripheral - receiver device attributes discovery failed!");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }

  BLECharacteristic ephemeralCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);
    
  if (!ephemeralCharacteristic) {
    Serial.println("* Peripheral - receiver device does not have ephemeral characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ephemeralCharacteristic.canWrite()) {
    Serial.println("* Peripheral - receiver does not have a writable ephemeral characteristic!");
    peripheral.disconnect();
    return;
  }

  byte collectedData[10][NUM_HASH_BYTES*2+1];
  int count = 0;

  while (peripheral.connected()) {
    String ephemeralID = generateEphemeralIDSha256(deviceSeed);
    Serial.print("Sent: ");
    Serial.println(ephemeralID);
    Serial.println(" ");
    byte values[NUM_HASH_BYTES*2+1];
    ephemeralID.getBytes(collectedData[count], NUM_HASH_BYTES*2 + 1);
    ephemeralCharacteristic.writeValue(collectedData[count], NUM_HASH_BYTES*2);
    delay(1000);
    count++;
    if (count == 9)
      break;
  }

  for (int i = 0; i < 10; ++i) {
    Serial.println(String((char *) collectedData[i]));
  }
  while(1);
  
  Serial.println("Peripheral - receiver device disconnected!");
}


String generateEphemeralIDSha256(String seed) {
  unsigned long timestamp = millis();
  String combinedData = seed + String(timestamp);  
  String ephemeralID = calculateSHA256(combinedData);
  Serial.println(combinedData);
  return ephemeralID;
}


String calculateSHA256(String input)
{
  SHA256 sha256;
  
  uint8_t hash_result[NUM_HASH_BYTES];
  
  sha256.reset();
  sha256.update(input.c_str(), input.length());
  sha256.finalize(hash_result, sizeof(hash_result));
  
  String hex_result = "";
  for (size_t i = 0; i < NUM_HASH_BYTES; i++) {
    hex_result += String(hash_result[i], HEX);
  }
  
  return hex_result;
}
