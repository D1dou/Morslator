#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void remove_extension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot) {
        *dot = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_fichier>.txt\n", argv[0]);
        return 1;
    }

    FILE *input_file, *output_file;
    char input_filename[FILENAME_MAX], output_filename[FILENAME_MAX];
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    strncpy(input_filename, argv[1], FILENAME_MAX - 1);
    input_filename[FILENAME_MAX - 1] = '\0';

    strncpy(output_filename, input_filename, FILENAME_MAX - 1);
    remove_extension(output_filename);
    strncat(output_filename, "_encrypted.txt", FILENAME_MAX - strlen(output_filename) - 1);

    input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", input_filename);
        return 1;
    }

    output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("Erreur : impossible de créer le fichier %s.\n", output_filename);
        fclose(input_file);
        return 1;
    }

    // Générer une clé et un vecteur d'initialisation aléatoires
    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    // Écrire la clé et le vecteur d'initialisation dans le fichier de sortie
    fwrite(key, 1, sizeof(key), output_file);
    fwrite(iv, 1, sizeof(iv), output_file);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char buffer[4096], encrypted_buffer[4096 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, encrypted_bytes;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        EVP_EncryptUpdate(ctx, encrypted_buffer, &encrypted_bytes, buffer, bytes_read);
        fwrite(encrypted_buffer, 1, encrypted_bytes, output_file);
    }

    EVP_EncryptFinal_ex(ctx, encrypted_buffer, &encrypted_bytes);
    fwrite(encrypted_buffer, 1, encrypted_bytes, output_file);

    EVP_CIPHER_CTX_free(ctx);

    fclose(input_file);
    fclose(output_file);
    printf("Le fichier a été chiffré avec succès en AES et sauvegardé dans le fichier %s.\n", output_filename);
    return 0;
}
