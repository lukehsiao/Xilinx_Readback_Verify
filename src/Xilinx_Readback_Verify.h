
#include <stdio.h>
#include <stdint.h> // for keeping things 32-bit

//----------------------------------------------------------------------------
// User must edit these values to match the FPGA being used
#define WORDS_PER_FRAME 101
//----------------------------------------------------------------------------


#define WORD_SIZE 33 // extra bit for null terminator
#define TRUE 1
#define FALSE 0

uint32_t convert_ascii_to_binary(char* ascii_string);

uint32_t verify_readback_word(uint32_t data, uint32_t gold, uint32_t mask);

uint32_t verify_full_readback(FILE* readback_data, FILE* rbd_file, FILE* msd_file);

void output_golden_binary();
