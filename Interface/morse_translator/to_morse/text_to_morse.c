#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tableau de correspondance du code Morse
const char* morse_code[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void char_to_morse(char c, char *output) {
    if (isalpha(c)) {
        strncpy(output, morse_code[toupper(c) - 'A'], 6);
    } else if (isdigit(c)) {
        strncpy(output, morse_code[c - '0' + 26], 6);
    } else {
        output[0] = '\0';
    }
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

    strncpy(input_filename, argv[1], FILENAME_MAX - 1);
    input_filename[FILENAME_MAX - 1] = '\0';

    strncpy(output_filename, input_filename, FILENAME_MAX - 1);
    remove_extension(output_filename);
    strncat(output_filename, "_morse.txt", FILENAME_MAX - strlen(output_filename) - 1);

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

    int first_char = 1;
    while ((ch = fgetc(input_file)) != EOF) {
        if (isalnum(ch)) {
            char_to_morse(ch, morse);
            if (!first_char) {
                fprintf(output_file, " ");
            }
            fprintf(output_file, "%s", morse);
            first_char = 0;
        } else if (ch == ' ' || ch == '\n') {
            fprintf(output_file, " / ");
            first_char = 1;
        }
    }

    fprintf(output_file, "\n"); // Ajout d'un saut de ligne à la fin du fichier

    fclose(input_file);
    fclose(output_file);
    printf("La traduction en Morse a été sauvegardée dans le fichier %s.\n", output_filename);
    return 0;
}
