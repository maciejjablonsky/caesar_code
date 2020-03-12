#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cli.h"
#include "exit_codes.h"

void encrypt_file(FILE *input, FILE *output, args_t *cli_arguments);
void decrypt_file(FILE *input, FILE *output, args_t *cli_arguments);

int main(int argc, char **argv)
{
    args_t *cli_arguments = args__ctor();
    dispatch_cli_options(cli_arguments, argc, argv, ":d:e:k:o:hv");
    FILE *input_file = get_input_file(cli_arguments);
    FILE *output_file = get_output_file(cli_arguments);
    if (is_encryption(cli_arguments))
    {
        encrypt_file(input_file, output_file, cli_arguments);
    }
    else if (is_decryption(cli_arguments))
    {
        decrypt_file(input_file, output_file, cli_arguments);
    }
    cli_arguments = args__dctor(cli_arguments);
    return EXIT_OK;
}
