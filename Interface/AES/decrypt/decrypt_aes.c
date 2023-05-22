#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void remove_extension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot) {
        *dot = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_fichier>_encrypted.txt\n", argv[0]);
        return 1;
    }

    FILE *input_file, *output_file;
    char input_filename[FILENAME_MAX], output_filename[FILENAME_MAX];
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

    strncpy(input_filename, argv[1], FILENAME_MAX - 1);
    input_filename[FILENAME_MAX - 1] = '\0';

    strncpy(output_filename, input_filename, FILENAME_MAX - 1);
    remove_extension(output_filename);
    strncat(output_filename, "_decrypted.txt", FILENAME_MAX - strlen(output_filename) - 1);

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

    // Lire la clé et le vecteur d'initialisation du fichier d'entrée
    fread(key, 1, sizeof(key), input_file);
    fread(iv, 1, sizeof(iv), input_file);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char buffer[4096], decrypted_buffer[4096 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, decrypted_bytes, final_decrypted_bytes;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        EVP_DecryptUpdate(ctx, decrypted_buffer, &decrypted_bytes, buffer, bytes_read);
        fwrite(decrypted_buffer, 1, decrypted_bytes, output_file);
    }

    EVP_CIPHER_CTX_set_padding(ctx, 0);
    if (EVP_DecryptFinal_ex(ctx, decrypted_buffer, &final_decrypted_bytes) > 0) {
        fwrite(decrypted_buffer, 1, final_decrypted_bytes, output_file);
    }

    EVP_CIPHER_CTX_free(ctx);

    fclose(input_file);
    fclose(output_file);
    printf("Le fichier a été déchiffré avec succès et sauvegardé dans le fichier %s.\n", output_filename);
    return 0;
}
