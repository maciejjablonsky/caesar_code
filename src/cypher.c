#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "cli.h"

bool is_between(int value, int low, int high)
{
    return low <= value && value <= high;
}

size_t modulo(int value, int n)
{
    int result = value % n;
    return (result < 0) ? result + n : result;
}

uchar_t *encryption(const uchar_t *message, int key)
{
    size_t length = strlen((char*)message);
    uchar_t *encrypted = (uchar_t *)calloc(length + 1, sizeof(uchar_t));
    for (size_t i = 0; i < length; ++i)
    {
        encrypted[i] = message[i];
        if (isalnum(message[i]))
        {
            char lower_bound = 0, higher_bound = 0;
            if (islower(message[i]))
            {
                lower_bound = 'a';
                higher_bound = 'z';
            }
            else if (isupper(message[i]))
            {
                lower_bound = 'A';
                higher_bound = 'Z';
            }
            else if (isdigit(message[i]))
            {
                lower_bound = '0';
                higher_bound = '9';
            }
            encrypted[i] += modulo(key, higher_bound - lower_bound + 1);

            if (!is_between(encrypted[i], lower_bound, higher_bound))
            {
                encrypted[i] = modulo(encrypted[i] - lower_bound, higher_bound - lower_bound + 1) + lower_bound;
            }
        }
    }
    return encrypted;
}

uchar_t *decryption(const uchar_t *encrypted, int key)
{
    return encryption(encrypted, -key);
}

void encrypt_file(FILE *input, FILE *output, args_t *cli_arguments)
{
#define BUFFER_SIZE 1024
    uchar_t buffer[BUFFER_SIZE + 1] = {0};
    while (fgets((char*)buffer, BUFFER_SIZE, input))
    {
        uchar_t *encrypted = encryption(buffer, get_encryption_key(cli_arguments));
        if (is_verbose(cli_arguments))
        {   
            printf("INPUT : %s"
                    "OUTPUT: %s\n", buffer, encrypted);
        }
        fputs((char*)encrypted, output);
        free(encrypted);
    }

#undef BUFFER_SIZE
}

void decrypt_file(FILE *input, FILE *output, args_t *cli_arguments)
{
#define BUFFER_SIZE 512
    uchar_t buffer[BUFFER_SIZE + 1] = {0};
    while (fgets((char*)buffer, BUFFER_SIZE, input))
    {
        uchar_t *decrypted = decryption(buffer, get_encryption_key(cli_arguments));
        if (is_verbose(cli_arguments))
        {
            printf("INPUT : %s"
                    "OUTPUT: %s\n", buffer, decrypted);
        }
        fputs((char*)decrypted, output);
        free(decrypted);
    }
#undef BUFFER_SIZE
}