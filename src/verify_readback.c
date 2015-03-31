// This is the driver file for verifying readback files
// author: Luke Hsiao
// 30 March 2015

#include "Xilinx_Readback_Verify.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Parse commandline arguments
    int i;
		for(i = 1; i < argc; i++){
			if(compare(argv[i], "-h") == 0){
				printf("USAGE: ./verify_readback [mask file] [rbd file]\n");
				return 0;
			}
		}
    
    FILE* rbd_file;
    FILE* msd_file;
    data_file = fopen("../tests/sample/sample1_readback.data", "rb");
    rbd_file = fopen("../tests/sample/sample1.rbd", "r");
    msd_file = fopen("../tests/sample/sample1.msd", "r");
    
    if (data_file == NULL) {
      printf("Could not open readback data file\n");
    }
    else if (rbd_file == NULL) {
      printf("Could not open RBD Golden File\n");
    }
    else if (msd_file == NULL) {
      printf("Could not open MSD file\n");
    }
    
    // Create Golden File
    output_golden_binary(FILE* rbd_file, FILE* msd_file);
    
    fclose(data_file);
    fclose(rbd_file);
    fclose(msd_file);
}