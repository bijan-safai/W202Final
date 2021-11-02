#include <AES.h>
#include <RNG.h>

//256 bit key
const int keyLen = 32;
const int messageSize = 16;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  // gen/set key
  byte keyBuffer[keyLen];
  
  RNG.begin("bijansamazingkeyworld");
  RNG.rand(keyBuffer, keyLen);

  AES256 *aes = new AES256();
  aes->setKey(keyBuffer, keyLen);

  // test message
  byte message[messageSize] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

  Serial.println("Message:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(message[i]);
    Serial.print(",");
  }
  Serial.println("");

  byte cipherText[messageSize];
  aes->encryptBlock(cipherText, message);

  Serial.println("Cipher:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(cipherText[i]);
    Serial.print(",");
  }
  Serial.println("");

  byte clearBuffer[messageSize];
  aes->decryptBlock(clearBuffer, cipherText);
  
  Serial.println("Clear:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(clearBuffer[i]);
    Serial.print(",");
  }
  Serial.println("");
 }

void loop() {
  // put your main code here, to run repeatedly:

}
