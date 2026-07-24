#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("image.png", "rb");

    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    unsigned char byte;

    fread(&byte, sizeof(unsigned char), 1, fp);

    printf("First stupid byte: 0x%02X\n", byte);

    fclose(fp);

    return EXIT_SUCCESS;
}
