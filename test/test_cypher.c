#include "unity.h"

#include "cypher.h"
#include <stdlib.h>
#include <string.h>
#include "cli.h"

#define LEN(ARRAY) (sizeof (ARRAY) / sizeof(*ARRAY))



typedef struct record
{
    uchar_t *value;
    uchar_t *encrypted;
} record_t;

record_t *RECORDS;
int KEY;
size_t LENGTH;

record_t records_key_2[] = {
    {"aaaa", "cccc"},
    {" .AbCd?\t", " .CdEf?\t"},
    {"haloHalo.\n", "jcnqJcnq.\n"},
    {"azza?", "cbbc?"},
    {"AZZA", "CBBC"},
    {"  asdf1234 ?/. ,", "  cufh3456 ?/. ,"}};

record_t records_key_32[] = {
    {"aa", "gg"},
    {"890123", "012345"}
};

record_t records_key_1000[] = {
    {"AaZz?/", "MmLl?/"},
    {"aaaa", "mmmm"},
    {"WwQq  t", "IiCc  f"},
    {"1234", "1234"}
};

record_t records_key_minus_34[] = {
    {"aaaa","ssss"},
    {"AaZz?/", "SsRr?/"}
};

record_t records_key_6[] = {
    {"Zrozumialy", "Fxufasogre"}
};

void setUp(void)
{
    TEST_ASSERT_EQUAL(26, 'Z' - 'A' + 1);
    TEST_ASSERT_EQUAL(26, 'z' - 'a' + 1);
    TEST_ASSERT_EQUAL(10, '9' - '0' + 1);
    
}

void tearDown(void)
{
    RECORDS = NULL;
}

void test_encryption(void)
{
    RECORDS = records_key_2;
    KEY = 2;
    for (int i = 0; i < LEN(records_key_2); ++i)
    {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, encryption(RECORDS[i].value, KEY));
    }
}

void test_decryption(void)
{
    RECORDS = records_key_2;
    KEY = 2;
    for (int i = 0; i < LEN(records_key_2); ++i)
    {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, decryption(RECORDS[i].encrypted, KEY));
    }
}

void test_negative_key_encryption(void)
{
    RECORDS = records_key_2;
    KEY = -2;
    for (int i = 0; i < LEN(records_key_2); ++i)
    {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, encryption(RECORDS[i].encrypted, KEY));
    }
}

void test_negative_key_decryption(void)
{
    RECORDS = records_key_2;
    KEY = -2;
    for (size_t i = 0; i < LEN(records_key_2); i++)
    {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, decryption(RECORDS[i].value, KEY));
    }
}

void test_key_1000_encryption(void) {
    RECORDS = records_key_1000;
    KEY = 1000;
    TEST_ASSERT_EQUAL(12, modulo(1000, 'Z' - 'A' + 1));
    for (size_t i = 0; i < LEN(records_key_1000); ++i) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, encryption(RECORDS[i].value, KEY));
    }
}

void test_key_1000_decryption(void) {
    RECORDS = records_key_1000;
    KEY = 1000;
    TEST_ASSERT_EQUAL(12, modulo(1000, 'Z' - 'A' + 1));
    for (size_t i = 0; i < LEN(records_key_1000); ++i) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, decryption(RECORDS[i].encrypted, KEY));
    }
}

void test_key_32_encryption(void) {
    RECORDS = records_key_32;
    KEY = 32;
    for (size_t i = 0; i < LEN(records_key_32); ++i) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, encryption(RECORDS[i].value, KEY));
    }
}

void test_key_32_decryption(void) {
    RECORDS = records_key_32;
    KEY = 32;
    for (size_t i = 0; i < LEN(records_key_32); ++i) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, decryption(RECORDS[i].encrypted, KEY));
    }
}

void test_modulo(void)
{
    TEST_ASSERT_EQUAL(0, modulo(5, 5));
    TEST_ASSERT_EQUAL(2, modulo(12, 5));
    TEST_ASSERT_EQUAL(8, modulo(-2, 10));
    TEST_ASSERT_EQUAL(8, modulo(34, 26));
    TEST_ASSERT_EQUAL(2, modulo(-10, 3));
    TEST_ASSERT_EQUAL(12, modulo(1000, 26));
    TEST_ASSERT_EQUAL(4, modulo(-1, 5));
    TEST_ASSERT_EQUAL(0, modulo(5, 5));
    TEST_ASSERT_EQUAL(4, modulo(4, 5));
    TEST_ASSERT_EQUAL(0, modulo(-10, 5));
}

void test_xor(void) {
    TEST_ASSERT_TRUE(xor(true, false));
    TEST_ASSERT_TRUE(xor(false, true));
    TEST_ASSERT_FALSE(xor(true, true));
    TEST_ASSERT_FALSE(xor(true, true));
}

void test_key_minus_34_encryption(void) {
    RECORDS = records_key_minus_34;
    KEY = -34;
    for (size_t i = 0; i < LEN(records_key_minus_34); i++) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, encryption(RECORDS[i].value, KEY));
    }
}

void test_key_minus_34_decryption(void) {
    RECORDS = records_key_minus_34;
    KEY = -34;
    for (size_t i = 0; i < LEN(records_key_minus_34); i++) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, decryption(RECORDS[i].encrypted, KEY));
    }
}

void test_key_6_decryption(void) {
    RECORDS = records_key_6;
    KEY = 6;
    for (size_t i = 0; i < LEN(records_key_6); i++) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].value, decryption(RECORDS[i].encrypted, KEY));
    }
}

void test_key_6_encryption(void) {
    RECORDS = records_key_6;
    KEY = 6;
    for (size_t i = 0; i < LEN(records_key_6); i++) {
        TEST_ASSERT_EQUAL_STRING(RECORDS[i].encrypted, encryption(RECORDS[i].value, KEY));
    }
}