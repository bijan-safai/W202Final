#include <ChaCha.h>
#include <RNG.h>

//256 bit key, 64 bit nonce
const int keyLen = 32;
const int nonceLen = 8;
const int messageSize = 64;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  byte keyBuffer[keyLen];
  byte nonceBuffer[nonceLen];

  byte message[messageSize] = {0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
                    0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  Serial.println("");

  // generate key and nonce
  RNG.begin("bijanskeyland");
  RNG.rand(keyBuffer, keyLen);
  RNG.rand(nonceBuffer, nonceLen);
  
  // set up chacha
  ChaCha *cha = new ChaCha();
  setupChaCha(cha, keyBuffer, nonceBuffer); 
  
  Serial.println("Message:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(message[i]);
    Serial.print(",");
  }
  Serial.println("");

  byte cipherText[messageSize];
  memset(cipherText, 0xBA, sizeof(cipherText));

  // to encrypt as a 64 byte block
  cha->encrypt(cipherText, message, messageSize);

  /*// to encrypt byte by byte (or by any byte block size you wish)
  for(int i = 0; i < messageSize; i++)
  {
    cha->encrypt(cipherText+i, message+1, 1);
  }*/

  Serial.println("Cipher:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(cipherText[i]);
    Serial.print(",");
  }
  Serial.println("");

  // it is critical to reset the state of ChaCha between crypto operations
  setupChaCha(cha, keyBuffer, nonceBuffer);
  
  byte clearText[messageSize];
  memset(clearText, 0xBA, sizeof(clearText));

  // to decrypt a single 64 byte block
  cha->decrypt(clearText, cipherText, messageSize);

  // to decrypt byte by byte (or by any byte block size)
 /* for(int i = 0; i < messageSize; i++)
  {
    cha->decrypt(clearText+i, cipherText+i, 1);
  }*/
  
  Serial.println("Clear:");
  for(int i = 0; i < messageSize; i++)
  {
    Serial.print(clearText[i]);
    Serial.print(",");
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}

void setupChaCha(ChaCha *cha, byte keyBuffer[], byte nonceBuffer[])
{
  cha->clear();
  if(!cha->setKey(keyBuffer, keyLen))
  {
    Serial.print("bad key");
  }
  if(!cha->setIV(nonceBuffer, nonceLen))
  {
    Serial.print("bad nonce");
  }
}
