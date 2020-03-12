#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <stdbool.h>
#include <stdio.h>

struct args;
typedef struct args args_t;

typedef unsigned char uchar_t;

args_t *args__ctor(void);
args_t *args__dctor(args_t *arguments);
args_t *dispatch_cli_options(args_t *arguments, int argc, char **argv, const char *available_options);

bool is_encryption(args_t *cli_arguments);
bool is_decryption(args_t *cli_arguments);
bool is_verbose(args_t *cli_arguments);
bool is_passing_rules(args_t *cli_arguments);
FILE *get_input_file(args_t * cli_arguments);
FILE *get_output_file(args_t * cli_arguments);
int get_encryption_key(args_t *cli_arguments);
void print_example_usage(void);
void print_help(void);
bool xor(bool p, bool q);
#endif // COMMAND_LINE_H
