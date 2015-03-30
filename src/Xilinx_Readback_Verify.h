
#include <stdio.h>

#define WORD_SIZE 33 // extra bit for null terminator

unsigned convert_ascii_to_binary(char* ascii_string);

unsigned verify_readback_word(unsigned data, unsigned gold, unsigned mask);
