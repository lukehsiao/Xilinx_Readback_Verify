
#CC = gcc
CFLAGS  = -g -Wall -coverage

C_SRCS = \
./unity/unity.c \
./unity/unity_fixture.c \
../src/Xilinx_Readback_Verify.c \
./test_runners/TestProductionCode_Runner.c \
./test_runners/all_tests.c \
./TestProductionCode.c \


INC_DIRS = -I./unity -I../src


EXE = unit_test

all: clean default

default:
	$(CC) $(CFLAGS) $(INC_DIRS) $(C_SRCS) -o $(EXE)
	./$(EXE) #run the unit tests
	
clean:
	rm -f $(EXE)
