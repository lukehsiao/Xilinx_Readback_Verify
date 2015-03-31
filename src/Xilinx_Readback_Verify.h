
#include <stdio.h>

//----------------------------------------------------------------------------
// User must edit these values to match the FPGA being used
#define WORDS_PER_FRAME 101
//----------------------------------------------------------------------------


#define WORD_SIZE 33 // extra bit for null terminator
#define TRUE 1
#define FALSE 0

unsigned convert_ascii_to_binary(char* ascii_string);

unsigned verify_readback_word(unsigned data, unsigned gold, unsigned mask);

unsigned verify_full_readback(FILE* readback_data, FILE* rbd_file, FILE* msd_file);

void output_golden_binary();
