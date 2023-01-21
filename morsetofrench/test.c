#include <stdio.h> // pour utiliser printf()
#include <stdlib.h> // pour utiliser malloc() et free()
#include <string.h>
#include "parser.h"

const char *morse_codes[] = {
    ".-",   // a
    "-...", // b
    "-.-.", // c
    "-..",  // d
    ".",    // e
    "..-.", // f
    "--.",  // g
    "....", // h
    "..",   // i
    ".---", // j
    "-.-",  // k
    ".-..", // l
    "--",   // m
    "-.",   // n
    "---",  // o
    ".--.", // p
    "--.-", // q
    ".-.",  // r
    "...",  // s
    "-",    // t
    "..-",  // u
    "...-", // v
    ".--",  // w
    "-..-", // x
    "-.--", // y
    "--.."  // z
};

int main()
{
    char text[] = "hello world";
    morse_tree_code tree = construct_tree(morse_codes);
    if(tree == NULL)
    {
        printf("Error: unable to construct tree.\n");
        return 1;
    }

    // Test le décodage de la string en code morse
    char morse_code[] = ".... . .-.. .-.. --- / -.. .- --..-- / .- .. .-.. -..";
    char decoded_text[100];
    if (decode(tree, morse_code, decoded_text) != 0)
    {
        printf("Error: unable to decode morse code.\n");
        return 1;
    }
    printf("Decoded text: %s\n", decoded_text);

    // Test encoding une phrase d'un text en morse
    char encoded_morse_code[100];
    if (encode(tree, text, encoded_morse_code) != 0)
    {
        printf("Error: unable to encode test to morse.\n");
        return 1;
    }
    printf("Encoded morse code: %s\n", encoded_morse_code);

    free_tree(tree);
    return 0;
}
