#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* text_to_hex(char* text)
{
    size_t len = strlen(text);
    char* hex = malloc(len*2 + 1);

    for(int i = 0; i < len; ++i)
    {
        sprintf(hex+i*2, "%02x", text[i]);
    }

    hex[len*2] = '\0';
    return hex;
}

char* hex_to_text(char* hex)
{
    size_t len = strlen(hex);
    char* text = malloc(len/2 + 1);

    for(int i = 0; i < len; i += 2)
    {
        sscanf(hex+i, "%2hhx", &text[i/2]);
    }

    text[len/2] = '\0';
    return text;
}

int main()
{
    char text[] = "Hello, world!";
    char* hex = text_to_hex(text);
    printf("%s\n", hex);  // Affiche "48656c6c6f2c20776f726c6421"

    char* text2 = hex_to_text(hex);
    printf("%s\n", text2);  // Affiche "Hello, world!"

    free(hex);
    free(text2);

    return 0;
}
