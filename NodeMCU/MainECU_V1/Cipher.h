#ifndef CIPHER_H_
#define CIPHER_H_

#include "mbedtls/aes.h"
#include <Arduino.h>
//#include <WString.h>


#define CIPHER_DEBUG
#define CIPHER_KEY                    "abcdefghijklmnop"

class Cipher {
public:
  /** Default constructor, privateChiperKey property will be set on a default, unsecure value
   *
   *  @param  ---
   *  @return ---
  */
  Cipher();
  
  /** Overloaded constructor, privateChiperKey will be set on @param key
   *
   *  @param key secure key as pointer on char array
   *  @return ---
  */
	Cipher(char * key);

  /** Default destructor, privateChiperKey will deleted
   *
   *  @param  ---
   *  @return ---
  */
  virtual ~Cipher();


  /** Set privateChiperKey on given @param key
   *
   *  @param key secure key as pointer on char array
   *  @return ---
  */
  void setKey(char * key);

  /** Returns the privateCipherKey
   *
   *  @param  ---
   *  @return secure key as pointer on char array
  */  
  char * getKey();


  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText char array with given key and store the output in @return outputBuffer
   *
   *  @param plainText buffer of length 16 characters
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function encrypt()
   *  @return outputBuffer buffer of length 16 characters filled with the encryption result
  */ 
	void encrypt(char * plainText, char * key, unsigned char * outputBuffer);

  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText char array with @property privateCipherKey and store the output in @return outputBuffer
   *
   *  @param plainText buffer of length 16 characters
   *  @return outputBuffer buffer of length 16 characters filled with the encryption result
  */ 
  void encrypt(char * plainText, unsigned char * outputBuffer);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText char array with given key and store the output in @return outputBuffer
   *
   *  @param cipherText buffer of length 16 characters
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function decrypt()
   *  @return outputBuffer buffer of length 16 characters filled with the decryption result
  */  
  void decrypt(unsigned char * cipherText, char * key, unsigned char * outputBuffer);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText char array with @property privateCipherKey and store the output in @return outputBuffer
   *
   *  @param cipherText buffer of length 16 characters
   *  @return outputBuffer buffer of length 16 characters filled with the decryption result
  */  
  void decrypt(unsigned char * cipherText, unsigned char * outputBuffer);


  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText char array buffer with given key and return @return cipherTextString as result
   *
   *  @param plainText buffer of length 16 characters
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function encryptBuffer()
   *  @return cipherTextString String of length 16 characters filled with the encryption result
  */
  String encryptBuffer(char * plainText, char * key);

  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText char array buffer with @property privateCipherKey and return @return cipherTextString as result
   *
   *  @param plainText buffer of length 16 characters
   *  @return cipherTextString String of length 16 characters filled with the encryption result
  */
  String encryptBuffer(char * plainText);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText string with given key and return @return decipheredTextString as result
   *
   *  @param cipherText string of length 16 characters
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function decryptBuffer()
   *  @return decipheredTextString String of length 16 characters filled with the decryption result
  */
  String decryptBuffer(String cipherText, char * key);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText string with @property privateCipherKey and return @return decipheredTextString as result
   *
   *  @param cipherText string of length 16 characters
   *  @return decipheredTextString String of length 16 characters filled with the decryption result
  */
  String decryptBuffer(String cipherText);


  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText string with given key and return @return cipherTextString as result
   *
   *  @param plainText string of variable length; ending with default ending character '\0'
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function encryptString()
   *  @return cipherTextString String of variable length filled with the encryption result
  */
  String encryptString(String plainText, char * key);

  /** Encrypt (AES-128bit ECB encryption mode) the @param plainText string with @property privateCipherKey and return @return cipherTextString as result
   *
   *  @param plainText string of variable length; ending with default ending character '\0'
   *  @return cipherTextString String of variable length filled with the encryption result
  */
  String encryptString(String plainText);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText string with given key and return @return decipheredTextString as result
   *
   *  @param cipherText string of variable length; ending with default ending character '\0'
   *  @param key secure key as pointer on char array, function call getKey() is possible, instead of using the second function decryptString()
   *  @return decipheredTextString String of length 16 characters filled with the decryption result
  */
  String decryptString(String cipherText, char * key);

  /** Decrypt (AES-128bit ECB decryption mode) the @param cipherText string with @property privateCipherKey and return @return decipheredTextString as result
   *
   *  @param cipherText string of variable length; ending with default ending character '\0'
   *  @return decipheredTextString String of length 16 characters filled with the decryption result
  */
  String decryptString(String cipherText);
  
private:
	char * privateCipherKey;
};

#endif /* CIPHER_H_ */
