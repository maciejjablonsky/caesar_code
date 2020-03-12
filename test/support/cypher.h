#ifndef CYPHER_H
#define CYPHER_H

#include <stdlib.h>

char *encryption(char *str, int key);
char *decryption(char *str, int key);
size_t modulo(int value, int n);
#endif // CYPHER_H
