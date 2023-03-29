#pragma once

//_________________________
//aes_encryption_decryption
//_________________________

extern unsigned char s[256];
extern unsigned char inv_s[256];
extern unsigned char mul2[];
extern unsigned char mul_3[];
extern unsigned char mul_9[];
extern unsigned char mul_11[];
extern unsigned char mul_13[];
extern unsigned char mul_14[];
extern unsigned char rcon[11];

unsigned char * g (unsigned char wInput[4], int counter);
unsigned char * keyExpansion(unsigned char key[16]);
void mixColumns(unsigned char * plainText);
void byteSubShiftRow(unsigned char * state);
void inverseByteSubShiftRow(unsigned char * plainText);
void AESEncryption(unsigned char * plainText, unsigned char * expandedKey, unsigned char * cipher);
void AESDecryption(unsigned char * cipher, unsigned char * expandedKey, unsigned char * plainText);
void printHex(unsigned char * data, int length);

//________
//blowfish
//________

typedef struct
{
    unsigned int p[18];
    unsigned int s[4][256];
} KeyStruct;

extern unsigned int default_p[];
extern unsigned int default_sBox[4][256];

unsigned long f (KeyStruct *ptr, unsigned int input);
void BlowfishEncryption(KeyStruct *ptr, unsigned int *left, unsigned int *right);
void keyExpansionBlowfish(KeyStruct *ptr, unsigned char key[8]);
void BlowfishDecryption(KeyStruct *ptr, unsigned int * left, unsigned int * right);

// ___
// rsa
// ___
void RSA(char *message, int mode);
