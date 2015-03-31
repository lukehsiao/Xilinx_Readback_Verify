
CC = gcc
CFLAGS  = -g -Wall -m32

C_SRCS = \
./Xilinx_Readback_Verify.c \
./verify_readback.c \


INC_DIRS = -I./

EXE = verify_readback

all: clean default

default:
	$(CC) $(CFLAGS) $(INC_DIRS) $(C_SRCS) -o $(EXE)
	
clean:
	rm -f $(EXE)
