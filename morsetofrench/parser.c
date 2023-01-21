#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"

size_t LONGUEUR_MAX_MORSE_CODE = 100;

morse_tree_code construct_tree(char *morse_codes[])
{
    morse_tree_code root = malloc(sizeof(struct morse_tree_node));
    if (root == NULL)
    {
        printf("Error: unable to construct tree.\n");
        return NULL;
    }

    root->right = NULL;
    root->left = NULL;
    root->value = ' ';

    if (morse_codes == NULL)
    {
        free(root);
        printf("Error: morse codes not found.\n");
        return NULL;
    }

    for(size_t k = 0; k<27; k++)
    {
        const char *letter = morse_codes[k];
		if (letter == NULL)
        {
            free_tree(root);
            printf("Error: invalid morse code.\n");
            return NULL;
        }

        morse_tree_code current = root;
        for(size_t j = 0; j<strlen(letter); j++)
        {
            if(letter[j] == '.')
            {
                if(current->left == NULL)
                {
                    morse_tree_code new = malloc(sizeof(struct morse_tree_node));
                    if(new == NULL)
                    {
                        free_tree(root);
                        printf("Error: unable to allocate memory.\n");
                        return NULL;
                    }

                    new->right = NULL;
                    new->left = NULL;
                    new->value = (k==26)?' ': (char)(97+k);
                    current->left = new;
                }
                current = current->left;
            }
            else if(letter[j] == '-')
            {
                if(current->right == NULL)
                {
                    morse_tree_code new = malloc(sizeof(struct morse_tree_node));
                    if(new == NULL)
                    {
                        free_tree(root);
                        printf("Error: unable to allocate memory.\n");
                        return NULL;
                    }
                    new->right = NULL;
                    new->left = NULL;
                    new->value = (k==26) ? ' ' : (char)(k+97);
                    current->right = new;
                }
                current = current->right;
            }
		}
	}
	return root;
}

// à utiliser une fois que l'on a utilisé l'arbre pour la mémoire :
// récursif
void free_tree(struct morse_tree_node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// fonction qui cherche récursivement si le caractère est dans l'arbre ou non et return son code morse associé
char* looking_for_letter(morse_tree_code root,char letter, char res[])
{
	if(root == NULL)
		return res;

    // cas de la feuille:
    if(root->value == letter)
        return "";
    // cas des noeuds internes:
    else
    {
        size_t len = strlen(res);
        if(root->left != NULL)
        {
            res[len] = '.';
            res[len+1] = '\0';
            looking_for_letter(root->left, letter, res);
        }
        if(root->right != NULL)
        {
            res[len] = '-';
            res[len+1] = '\0';
            looking_for_letter(root->right, letter, res);
        }
    }
	return res;
}

int encode(morse_tree_code tree, char text[], char morse_code[])
{
    int i = 0;
    int j = 0;
    while (text[i] != '\0') {
        char letter = text[i];
        if (letter == ' ') {
            morse_code[j] = ' ';
            j++;
        }
        else {
            letter = tolower(letter);
            char morse_letter[LONGUEUR_MAX_MORSE_CODE];
            looking_for_letter(tree, letter, morse_letter);
            if (strlen(morse_code) + strlen(morse_letter) >= LONGUEUR_MAX_MORSE_CODE) {
                printf("Error: morse code is too long.\n");
                return 1;
            }
            strcat(morse_code, morse_letter);
            j += strlen(morse_letter);
        }
        i++;
    }
    morse_code[j] = '\0';
    return 0;
}

int decode(morse_tree_code tree, char* morse_code, char* decoded_text) {
    morse_tree_code current_node = tree;
    int i = 0;
    int j = 0;
    while (morse_code[i] != '\0') {
        if (morse_code[i] == '.') {
            current_node = current_node->left;
        } else if (morse_code[i] == '-') {
            current_node = current_node->right;
        } else if (morse_code[i] == ' ' || morse_code[i] == '/') {
            if (current_node->value == '\0') {
                printf("Invalid morse code.\n");
                return 1;
            }
            decoded_text[j] = current_node->value;
            j++;
            current_node = tree;
        } else {
            printf("Invalid character in morse code: %c\n", morse_code[i]);
            return 1;
        }
        i++;
    }
    if (current_node->value == '\0') {
        printf("Invalid morse code.\n");
        return 1;
    }
    decoded_text[j] = current_node->value;
    decoded_text[j+1] = '\0';
	return 0;
}
