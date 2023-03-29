/*
 * C program to Implement the RSA Algorithm
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	if (n <= 1)
		return 0;

	int i;
    for (i = 2; i <=(int)naive_sqrt(n); i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int mod_inverse(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        // q est le quotient de la division de a par m
        q = a / m;
        t = m;

        // m est le reste de la division de a par m
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

/* Fonction qui génère un nombre premier aléatoire */
int generate_prime()
{
    int p;

    do
    {
        p = rand() % 1000;
    } while (!isPrime(p));

    return p;
}

/* Fonction qui calcule le modulo de a^b modulo m de manière efficace */
int mod_pow(int a, int b, int m)
{
    int res = 1;

    a = a % m;

    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % m;

        b = b >> 1;
        a = (a * a) % m;
    }

    return res;
}

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}
 
/* Fonction qui chiffre un message avec la clé publique */
void encrypt(char *message, int message_len, int e, int n, int *cipher)
{
    for (int i = 0; i < message_len; i++)
    {
        cipher[i] = mod_pow(message[i], e, n);
    }
} 

/* Fonction qui déchiffre un message avec la clé privée */
void decrypt(int *cipher, int cipher_len, int d, int n, unsigned char *message)
{
    for (int i = 0; i < cipher_len; i++)
    {
        message[i] = mod_pow(cipher[i], d, n);
    }
}

int main()
{
    int p, q, n, phi_n, e, d;
    char message[100];
    int cipher[100];
    int cipher_len;

    // Générer deux nombres premiers aléatoires
    p = generate_prime();
    q = generate_prime();

    // Calculer n et phi(n)
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // Choisir un entier e qui est premier avec phi(n)
    do
    {
        e = rand() % phi_n;
    } while (gcd(e, phi_n) != 1);

    // Calculer l'inverse modulaire de e modulo phi(n)
    d = mod_inverse(e, phi_n);

    printf("Clé publique : (%d, %d)\n", e, n);
    printf("Clé privée : (%d, %d)\n", d, n);

    // Demander à l'utilisateur d'entrer un message
    printf("Entrez un message à chiffrer (maximum 100 caractères) : ");
    fgets(message, 100, stdin);

    // Chiffrer le message avec la clé publique
    int message_len = strlen(message);
    encrypt(message, message_len, e, n, cipher);
    cipher_len = message_len;

    printf("Message chiffré : ");
    for (int i = 0; i < cipher_len; i++)
    {
        printf("%d ", cipher[i]);
    }
    printf("\n");

    // Déchiffrer le message avec la clé privée
    decrypt(cipher, cipher_len, d, n, message);

    printf("Message déchiffré : ");
    for (int i = 0; i < cipher_len; i++)
    {
        printf("%c", message[i]);
    }
    printf("\n");

    return 0;
}

