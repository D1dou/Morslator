#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tableau de correspondance du code Morse
const char* morse_code[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

char morse_to_char(const char *morse) {
    for (int i = 0; i < 36; i++) {
        if (strcmp(morse, morse_code[i]) == 0) {
            if (i < 26) {
                return 'A' + i;
            } else {
                return '0' + (i - 26);
            }
        }
    }
    return ' '; // Caractère inconnu
}

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
    char input_filename[FILENAME_MAX], output_filename[FILENAME_MAX], morse[6], ch;
    int index = 0;

    strncpy(input_filename, argv[1], FILENAME_MAX - 1);
    input_filename[FILENAME_MAX - 1] = '\0';

    strncpy(output_filename, input_filename, FILENAME_MAX - 1);
    remove_extension(output_filename);
    strncat(output_filename, "_result.txt", FILENAME_MAX - strlen(output_filename) - 1);

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", input_filename);
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Erreur : impossible de créer le fichier %s.\n", output_filename);
        fclose(input_file);
        return 1;
    }

    while ((ch = fgetc(input_file)) != EOF) {
        if (ch == '.' || ch == '-') {
            morse[index++] = ch;
        } else if (ch == ' ' || ch == '/') {
            morse[index] = '\0';
            fprintf(output_file, "%c", morse_to_char(morse));
            index = 0;
            if (ch == '/') {
                fprintf(output_file, " ");
            }
        }
    }

    fprintf(output_file, "\n"); // Ajout d'un saut de ligne à la fin du fichier

    fclose(input_file);
    fclose(output_file);
    printf("La traduction a été sauvegardée dans le fichier %s.\n", output_filename);
    return 0;
}
