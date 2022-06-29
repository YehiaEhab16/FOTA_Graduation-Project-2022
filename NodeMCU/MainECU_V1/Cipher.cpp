#include "Cipher.h"

Cipher::Cipher() {
  // default unsecure key, its highly recommended to use the overloaded constructor and the function setKey()
  // sometimes serval keys wont work 
  // https://tls.mbed.org/kb/how-to/generate-an-aes-key
  
  setKey("abcdefghijklmnop");
}

Cipher::Cipher(char * key) {
	setKey(key);
}

Cipher::~Cipher() {
	delete privateCipherKey;
}

void Cipher::setKey(char * key) {
  // aes-128bit mode means that your cipher key can only be 16 characters long 
  // futhermore, only chracters in the cipher key are allowed, not numbers!
  // 16 characters + '\0'
  
  if( strlen(key) > 16 ) {
    privateCipherKey = new char[17];
    (String(key).substring(0,16)).toCharArray(privateCipherKey, 17);
    
    #ifdef CIPHER_DEBUG
      Serial.println("[cipher] error: cipher key to long! Will be cutted to 16 characters.");
      Serial.println("[cipher] => " + String(key));
      Serial.println("[cipher] => " + String(privateCipherKey));
    #endif  
  } else if( strlen(key) < 16 ) {
    privateCipherKey = "abcdefghijklmnop";
    
    #ifdef CIPHER_DEBUG
      Serial.println("[cipher] error: cipher key to short! Standard cipher key will be used.");
    #endif
  } else {
    #ifdef CIPHER_DEBUG
      Serial.println("[cipher] cipher key length matched. Using this key.");
    #endif
    privateCipherKey = key;
  }
}

char * Cipher::getKey() {
  return privateCipherKey;
}

 
void Cipher::encrypt(char * plainText, char * key, unsigned char * outputBuffer) {
  // encrypt plainText buffer of length 16 characters
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void Cipher::encrypt(char * plainText, unsigned char * outputBuffer) {
  encrypt(plainText, getKey(), outputBuffer);
}

void Cipher::decrypt(unsigned char * cipherText, char * key, unsigned char * outputBuffer) {
  // encrypt ciphered chipherText buffer of length 16 characters to plain text
  mbedtls_aes_context aes;
 
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)cipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void Cipher::decrypt(unsigned char * cipherText, unsigned char * outputBuffer) {
  decrypt(cipherText, getKey(), outputBuffer);
}


String Cipher::encryptBuffer(char * plainText, char * key) {
  // returns encrypted String of plainText (length: 16 characters)
  String cipherTextString = "";
  unsigned char cipherTextOutput[16];
   
  encrypt(plainText, key, cipherTextOutput);
  
  for (int i = 0; i < 16; i++) {
    cipherTextString = cipherTextString + (char)cipherTextOutput[i];
  }

  return cipherTextString;
}

String Cipher::encryptBuffer(char * plainText) {
  return encryptBuffer(plainText, getKey());
}

String Cipher::decryptBuffer(String cipherText, char * key) {
  // returns decrypted String of ciphered text (length: 16 characters)
  String decipheredTextString = "";
  unsigned char cipherTextOutput[16];
  unsigned char decipheredTextOutput[16];

  for (int i = 0; i < 16; i++) {
    cipherTextOutput[i] = (char)cipherText[i];
  }
  
  decrypt(cipherTextOutput, key, decipheredTextOutput);

  for (int i = 0; i < 16; i++) {
    decipheredTextString = decipheredTextString + (char)decipheredTextOutput[i];

    if(decipheredTextString[i] == '\0') {
        break;
    }
  }

  return decipheredTextString;
}

String Cipher::decryptBuffer(String cipherText) {
  return decryptBuffer(cipherText, getKey());
}


String Cipher::encryptString(String plainText, char * key) {
  // returns encrypted String of plainText with variable length
  constexpr int BUFF_SIZE=16;
  String buffer = "";
  String cipherTextString = "";
  int index = plainText.length() / BUFF_SIZE;
  
  for(int block=0; block < plainText.length()/BUFF_SIZE; block++) {
      for(int j = block*BUFF_SIZE; j < (block+1)*BUFF_SIZE; j++) {
        buffer += plainText[j];
      }
      
      cipherTextString += encryptBuffer(const_cast<char*>(buffer.c_str()), key);
      buffer = "";
  }

  buffer="";

  if( plainText.length()%BUFF_SIZE > 0 ) {    
    for(int bytes_read=(index*BUFF_SIZE); bytes_read <= (index*BUFF_SIZE) + plainText.length()%BUFF_SIZE; bytes_read++) {
      buffer += plainText[bytes_read];
    };
    cipherTextString += encryptBuffer(const_cast<char*>(buffer.c_str()), key);
  }

  return cipherTextString;
}

String Cipher::encryptString(String plainText) {
  return encryptString(plainText, getKey());
}

String Cipher::decryptString(String cipherText, char * key) {
  // returns encrypted String of plainText with variable length
  constexpr int BUFF_SIZE=16;
  String buffer = "";
  String decipheredTextString = "";
  
  for(int block=0; block < cipherText.length()/BUFF_SIZE; block++) {
      for(int j = block*BUFF_SIZE; j < (block+1)*BUFF_SIZE; j++) {
        buffer += cipherText[j];
      }
      
      decipheredTextString += decryptBuffer(buffer, key);
      buffer = "";
  }

  return decipheredTextString;
}

String Cipher::decryptString(String cipherText) {
  return decryptString(cipherText, getKey());
}
