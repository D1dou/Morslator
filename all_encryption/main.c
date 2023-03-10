#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#define uint unsigned long

int main() {
    // Quelle encryption souhaitez-vous ?
goback:
    printf("Souhaitez-vous encrypter ou décrypter un texte, soldat ?\n'e' : encrypter, 'd' : décrypter");
    char begin[33];
    read(STDIN_FILENO, begin, 33);

    size_t nbChar = sizeof(begin)/sizeof(char);
    while (nbChar != 1)
    {
        printf("Mauvais formalisme...\n Retentez votre chance :\n'e' : encrypter, 'd' : décrypter");
        read(STDIN_FILENO, begin, 33);
        nbChar = sizeof(begin)/sizeof(char);
    }

    char c = begin[0];
    char choice[1] = {'\0'};
    int k = 0;
    
	// AES ENCRYPTION && DECRYPTION
	#define BLOCK_SIZE 16
	unsigned char aeskey[16];
    unsigned char plaintext[BLOCK_SIZE];
	unsigned char cipher[BLOCK_SIZE];
    unsigned char decrypted[BLOCK_SIZE];
    unsigned char * expandedKey;

	// BLOWFISH ENCRYPTION && DECRYPTION
    // Clé de chiffrement/déchiffrement
    unsigned char key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	KeyStruct keyStruct;

	// RSA ENCRYPTION
	char *msg = "Morslator is the best application !";

	switch(c)
    {
        case 'e':
        {
retry:
            printf("Veuillez choisir le mode d'encryption :\n - AES 128 : 'a' ;\n - RSA : 'r' ;\n - BLOWFISH : 'b' ; HEXADECIMAL : 'h' ; \nRETOUR : 'x'.\n");
            read(STDIN_FILENO, choice, 1);
            char thechoice = choice[0];
            switch (thechoice)
            {
                case 'a':
                {
                // AES ENCRYPTION && DECRYPTION

                    // Lecture de la clé d'encryption
                    printf("Enter the 16-byte key for encryption (in hex): ");
                    char input[33];
                    read(STDIN_FILENO, input, 33);
                    for (int i = 0; i < 16; i++) {
                        sscanf(input + i * 2, "%2hhx", &aeskey[i]);
                    }

                    // Lecture du bloc de texte clair
                    printf("Enter the plaintext (in hex, up to 16 bytes): ");
                    read(STDIN_FILENO, input, 33);
                    int input_len = strlen(input);
                    if (input_len % 2 != 0) {
                        printf("Invalid input length\n");
                        return 1;
                    }
                    int bytes_to_read = input_len / 2;
                    if (bytes_to_read > BLOCK_SIZE) {
                        printf("Input too large\n");
                        return 1;
                    }
                    for (int i = 0; i < bytes_to_read; i++) {
                        sscanf(input + i * 2, "%2hhx", &plaintext[i]);
                    }

                    // Génération de la clé étendue
                    expandedKey = keyExpansion(aeskey);

                    // Chiffrement du texte clair
                    AESEncryption(plaintext, expandedKey, cipher);

                    // Affichage du résultat chiffré
                    printf("Cipher: ");
                    printHex(cipher, BLOCK_SIZE);

					// Déchiffrement du texte chiffré
                    AESDecryption(cipher, expandedKey, decrypted);

                    // Affichage du texte déchiffré
                    printf("Decrypted: ");
                    printHex(decrypted, BLOCK_SIZE);

                    // Nettoyage de la mémoire
                    free(expandedKey);
                    break;
                }

                case 'b':
                {
                 // BLOWFISH ENCRYPTION && DECRYPTION

					// KeyStruct keyStruct;
                    keyExpansionBlowfish(&keyStruct, key);

					// Message à chiffrer/déchiffrer
                    char message[] = "Bonjour, ceci est un test de l'algorithme Blowfish.";
                    size_t messageLen = strlen(message);
                    printf("Message initial : %s\n", message);

                    // Conversion du message en un tableau d'entiers 32 bits
                    unsigned int *messageInts = (unsigned int *)message;
                    size_t messageIntsLen = messageLen / sizeof(unsigned int) + (messageLen % sizeof(unsigned int) ? 1 : 0);

                    // Chiffrement du message
                    for (unsigned int i = 0; i < messageIntsLen; i += 2)
                    {
                        BlowfishEncryption(&keyStruct, &messageInts[i], &messageInts[i + 1]);
                    }
                    printf("Message chiffre : ");
                    for (size_t i = 0; i < messageLen; i++)
                    {
                        printf("%02x", ((unsigned char *)messageInts)[i]);
                    }
                    printf("\n");

                    // Déchiffrement du message
                    for (size_t i = 0; i < messageIntsLen; i += 2)
                    {
                        BlowfishDecryption(&keyStruct, &messageInts[i], &messageInts[i + 1]);
                    }
                    printf("Message dechiffre : %s\n", message);
					break;
                }
                case 'h':
                {
                // RSA ENCRYPTION && DECRYPTION
					RSA(msg, 0);
					break;
				}
				case 'x':
				{
					goto goback;
				}
				default:
				{
					printf("Invalid choice\n");
					goto retry;
					break;
                }
            }
			//case 'd':
		    default:
            {
                printf("Invalid choice\n");
                goto goback;
                break;
            }
        }
    }//SWITCH
	return 0;
}
