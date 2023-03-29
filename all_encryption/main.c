#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <math.h>
#define uint unsigned long

// Fonctions auxiliaires pour RSA
double naive_sqrt(double number)
{
	if (number < 0)
	{
		fprintf(stderr, "Erreur : Nombre négatif.\n");
		return -1;
	}

	if (number == 0 || number == 1)
		return number;

	double precision = 0.00001;
	double sqrt_candidate = 0;

	while (sqrt_candidate * sqrt_candidate <= number)
		sqrt_candidate += precision;

	return sqrt_candidate;
}

int isPrime(int n)
{
    int i;
    for (i = 2; i <= (int)naive_sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}
 
int totient(int p, int q)
{
    return (p - 1) * (q - 1);
}

int randome(int lambda_n)
{
    printf("\nThe number e should be less than %d\n and greater than 1.",lambda_n);
    for (int i = 2; i < lambda_n; i++)
    {
        if (gcd(i, lambda_n) == 1)
        {
            return i;
        }
    }
    return -1;
}

int private_key(int e, int lambda_n)
{
    for (int i = 1; i < lambda_n; i++)
    {
        if ((i * e) % lambda_n == 1)
        {
            printf("\nThus, (i * e) %% lambda_n = 1, (%d * %d) %% %d = 1", i, e, lambda_n);
            return i;
        }
    }
    return -1;
}

long pomod(long a, long b, long m)
{
    long x = 1, y = a;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x * y) % m;
        }
        y = (y * y) % m;
        b /= 2;
    }
    return x % m;
}

/* Encryption
 * A function which takes the message, the public key and a number n which is the
 * product of p and q. The function encrypts the message using the public key
 * and returns the encrypted message.
 */

char *encrypt(char *message, long e, long n)
{
    long i;
    long len = strlen(message);
    char *cipher = (char *)malloc(len * sizeof(char));
    for (i = 0; i < len; i++)
    {
        cipher[i] = pomod(message[i], e, n);
        printf("\n%c -> %c", message[i], cipher[i]);
    }
    return cipher;
}

/* Decryption
 * A function which takes the cipher text, the private key and a number n which
 * is he product of p and q. The function decrypts the cipher text using the
 * private key and returns the decrypted message.
 */

char *decrypt(char *cipher, long d, long n)
{
    long i;
    long len = strlen(cipher);
    char *message = (char *)malloc(len * sizeof(char));
    for (i = 0; i < len; i++)
    {
        // message[i] = (long) pow(cipher[i], d) % n;
        message[i] = pomod(cipher[i], d, n);
        printf("\n%c -> %c", cipher[i], message[i]);
    }
    return message;
}

// ------------------------------

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
                // AES ENCRYPTION

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
                    printf("The expanded key : %lu\n
                            Keep it safe soldier.");

                    // Chiffrement du texte clair
                    AESEncryption(plaintext, expandedKey, cipher);

                    // Affichage du résultat chiffré
                    printf("Cipher: ");
                    printHex(cipher, BLOCK_SIZE);

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
                case 'r':
                {
                // RSA ENCRYPTION && DECRYPTION
					
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
            break;
        }
        case("d")
        {
retry2:
            printf("Veuillez choisir le mode de décryption :\n - AES 128 : 'a' ;\n - RSA : 'r' ;\n - BLOWFISH : 'b' ; HEXADECIMAL : 'h' ; \nRETOUR : 'x'.\n");
            read(STDIN_FILENO, choice, 1);
            char thechoice = choice[0];
            switch (thechoice)
            {
                case 'a':
                {
                    // AES DECRYPTION
                    printf("Entrez la clef 16-byte pour l'encryption (en hex): ");
                    unsigned char* expandedKey2;
                    scanf("%lu", &expandedKey2);

                    printf("Entrez le texte à déchiffrer : ");

                    // Déchiffrement du texte chiffré
                    AESDecryption(cipher2, expandedKey2, decrypted);

                    // Affichage du texte déchiffré
                    printf("Decrypted: ");
                    printHex(decrypted, BLOCK_SIZE);
            break;
        }
    }//SWITCH
	return 0;
}
