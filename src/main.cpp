// BLE S3 SERVER

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

/* BLEServer *pServer = BLEDevice::createServer();
BLEService *pService = pServer->createService(SERVICE_UUID);
BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       ); */

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

float num_float=0;
int brightness;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE Server!");

  

  pinMode(LED_BUILTIN, OUTPUT);

  BLEDevice::init("ESP32-BLE-Server");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  
  /* BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );*/

  pCharacteristic->setValue("Hello, World!");
  pService->start();
  //BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  //pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in the Client!");
}

void loop()
{
  std::string value = pCharacteristic->getValue();
  Serial.print("The new characteristic value is: ");
  //Serial.println(value.c_str());
  
  num_float = atof( value.c_str());
  Serial.println(num_float);

  if((num_float<20)&& (num_float>0)){
  digitalWrite(LED_BUILTIN,HIGH);  
  }
  else{
  digitalWrite(LED_BUILTIN,LOW);
  }
  delay(500);
}