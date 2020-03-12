#include "cli.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "exit_codes.h"
struct args_flags
{
    unsigned char encryption : 1;
    unsigned char decryption : 1;
    unsigned char verbose : 1;
    unsigned char output : 1;
    unsigned char key_given : 1;
    unsigned char input : 1;
};
typedef struct args_flags args_flags_t;

struct args
{
    args_flags_t flags;
    int key;
    char *input_path;
    char *output_path;
};

args_t *args__ctor(void)
{
    args_t *this = (args_t *)calloc(1, sizeof(args_t));
    if (this == NULL)
    {
        fprintf(stderr, "Memory error.\n");
        exit(EXIT_MALLOC_FAIL);
    }
    memset(this, 0, sizeof(args_t));
    return this;
}

args_t *args__dctor(args_t *this)
{
    if (this)
    {
        if (this->input_path) {
            free(this->input_path);
        }
        if (this->output_path) {
            free(this->output_path);
        }
        free(this);
    }
    return NULL;
}

args_t *dispatch_cli_options(args_t *this, int argc, char **argv, const char *available_options)
{
    extern char *optarg;
    int opt = 0;
    while ((opt = getopt(argc, argv, available_options)) != -1)
    {
        switch (opt)
        {
        case 'd':
            if (optarg)
            {
                this->flags.decryption = true;
                this->input_path = optarg;
                this->flags.input = true;
            }
            break;
        case 'e':
            if (optarg)
            {
                this->flags.encryption = true;
                this->input_path = optarg;
                this->flags.input = true;
            }
            break;
        case 'o':
            if (optarg)
            {
                this->flags.output = true;
                this->output_path = optarg;
            }
            break;
        case 'k':
            if (optarg)
            {
                this->key = atoi(optarg);
                this->flags.key_given = true;
            }
            break;
        case 'v':
            this->flags.verbose = true;
            break;
        case ':':
            printf("Option needs value.\n");
            exit(EXIT_NO_OPTION_VALUE);
            break;
        case 'h':
            print_help();
            exit(0);
            break;
        case '?':
            printf("Unknown option.\n");
            exit(EXIT_UNKNOWN_INSTRUCTION);
            break;
        }
    }
    if (!is_passing_rules(this)) {
        print_example_usage();
        exit(EXIT_INVALID_INSTRUCTION_SET);
    }
    return this;
}

bool is_encryption(args_t *this)
{
    return this->flags.encryption;
}

bool is_decryption(args_t *this)
{
    return this->flags.decryption;
}

FILE *get_input_file(args_t *this)
{
    FILE *file = fopen(this->input_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Cannot open input file %s\n", this->input_path);
        exit(EXIT_NO_OPTION_VALUE);
    }
    return file;
}

FILE *get_output_file(args_t *this)
{
    FILE *file = fopen(this->output_path, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Cannot open output file %s\n", this->output_path);
        exit(EXIT_NO_OPTION_VALUE);
    }
    return file;
}

bool encryption_rule(args_flags_t *flags)
{
    return flags->encryption && flags->key_given && flags->output && flags->input;
}

bool decryption_rule(args_flags_t *flags)
{
    return flags->decryption && flags->key_given && flags->output && flags->input;
}

bool is_passing_rules(args_t *this)
{
    args_flags_t *flags = &this->flags;
    // either one or another
    return xor(encryption_rule(flags), decryption_rule(flags));
}

int get_encryption_key(args_t *cli_arguments)
{
    return cli_arguments->key;
}

bool is_verbose(args_t *cli_arguments)
{
    return cli_arguments->flags.verbose;
}

void print_example_usage(void) {
    printf("Example usage: ./cypher -[e|d] <input_file_path> -o <output_file_path> -k <key_value>\n");
}

void print_help(void)  {
    printf(
        "\ncypher\t\tprogram to encrypt/decrypt file using caesar cypher\n\n"
        "\t-h\tprints this message\n"
        "\t-e\t<input_file> encrypt file\n"
        "\t-d\t<input_file> decrypt file\n"
        "\t-o\t<output_file> file that program will write output into\n"
        "\t-k\t<value> key used to encryption/decryption\n"
        "\t-v\tverbose mode\n"
    );
}

bool xor(bool p, bool q) {
    return (p || q) && !(p && q);
}

