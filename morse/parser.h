#pragma once

struct morse_tree_node {
    char value;
    struct morse_tree_node *left;
    struct morse_tree_node *right;
};

typedef struct morse_tree_node *morse_tree_code;

//extern size_t LONGUEUR_MAX_MORSE_CODE = 50;

//Prototypes des fonctions
morse_tree_code construct_tree();
int decode(morse_tree_code tree, char morse_code[], char text[]);
int encode(morse_tree_code tree, char text[], char morse_code[]);
void free_tree(morse_tree_code tree);
