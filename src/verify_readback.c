// This is the driver file for verifying readback files
// author: Luke Hsiao
// 30 March 2015

#include "Xilinx_Readback_Verify.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Parse commandline arguments
    int i;
		for(i = 1; i < argc; i++){
			if(compare(argv[i], "-info") == 0){
				printf("This function continuously writes the original configuration to memory without "
						"checking for errors\nBlind Scrubbing Options\n-r  Perform full read back before scrubbing "
						"from read back file\n-g <FileName>  Scrub using specified golden file (.rbd)\n");
				return 0;
			}else if(compare(argv[i], "-r") == 0){
				printf("Read back started\n");
				device_data = jtag_read_config_frame(JTAG_virtual_address, 0,
						ZYNQ_JTAG_SCRUBBER_NUMBER_OF_FRAMES_LOGIC, 0);
				FILE *f = fopen("read_back.data", "wb");
				fwrite(device_data, sizeof(int),
						ZYNQ_JTAG_SCRUBBER_NUMBER_OF_FRAMES_LOGIC*ZYNQ_JTAG_SCRUBBER_WORDS_PER_FRAME, f);
				fclose(f);
				printf("Read back finished\n");
			}
		}
}