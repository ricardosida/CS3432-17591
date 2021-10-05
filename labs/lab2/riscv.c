#define MAX_LIMIT 1000
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

bool equal(char* str, char str2[]);
char* rem(char* str);
char* rem2(char* str);

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){

	char** instructions = tokenize(instr);
	char add[20] = "ADD";
	char addi[20] = "ADDI";
	char lw[20] = "LW";
	char sw[20] = "SW";
	char and[20] = "AND";
	char or[20] = "OR";
	char xor[20] = "XOR";
	if (equal(instructions[0], add)){
		printf("succes");
		int value = atoi(rem(instructions[1]));
		int value2 = atoi(rem(instructions[2]));
		int value3 = atoi(rem(instructions[3]));
		
		reg[value] = reg[value2] + reg[value3];
		printf("%d %d %d",reg[value2],reg[value3],reg[value]);
		return true;

	}else if (equal(instructions[0], addi)){
		int value = atoi(rem(instructions[1]));
		int value2 = atoi(rem(instructions[2]));
		int value3 = atoi(instructions[3]);
		
		reg[value] = reg[value2] + reg[value3];
		return true;

	}else if(equal(instructions[0], lw)){
		char* mem_file = "mem.txt";
		int32_t address = (atoi(instructions[2]) + reg[atoi(rem2(instructions[3]))]);
		int value = atoi(rem(instructions[1]));
		int32_t read = read_address(address, mem_file);
		reg[value] = read;
		//printf("ADRESS %d", reg[value]);

		printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
		return true;

	}else if(equal(instructions[0], sw)){
		int32_t data_to_write = atoi(rem(instructions[1]));
		int32_t address = (atoi(instructions[2]) + reg[atoi(rem2(instructions[3]))]);
		char* mem_file = "mem.txt";


		int32_t write = write_address(data_to_write, address, mem_file);
		if(write == (int32_t) NULL)
			printf("ERROR: Unsucessful write to address %0X\n", 0x40);
		return true;

	}else if(equal(instructions[0], and)){
		int value = atoi(rem(instructions[1]));
		int value2 = atoi(rem(instructions[2]));
		int value3 = atoi(rem(instructions[3]));
		
		reg[value] = reg[value2] & reg[value3];

	}else if(equal(instructions[0], or)){
		int value = atoi(rem(instructions[1]));
		int value2 = atoi(rem(instructions[2]));
		int value3 = atoi(rem(instructions[3]));
		
		reg[value] = reg[value2] | reg[value3];

	}else if(equal(instructions[0], xor)){
		int value = atoi(rem(instructions[1]));
		int value2 = atoi(rem(instructions[2]));
		int value3 = atoi(rem(instructions[3]));
		
		reg[value] = reg[value2] ^ reg[value3];

	}
	return false;

}
bool equal(char* x, char* y){

    // Iterate a loop till the end
    // of both the strings
	int counter = 0;
	
    while (*x != '\0') {
		counter++;
        if (*x == *y) {
            x++;
            y++;
        }else{
			return false;
		}
    }
	if (counter == 0){
		return false;
	}
    return true;
	

}
//remove the X from register
char* rem(char* str){
	char* newPointer = (char*) malloc(2 * sizeof(char));
	int i = 0;
	for (char *p = str; *p; p++){
		if (i != 0){
			newPointer[i-1] = *p;
		}
		
        i++;
    }

	return newPointer;
}
//removes parenthesis and returns the string of the number
char* rem2(char* str){
	char* newPointer = (char*) malloc(2 * sizeof(char));
	int i = 0;
	for (char *p = str; *p; p++){
		if (*p == ')'){
			break;
		}
		if (i > 1){
			newPointer[i-2] = *p;
		}
		
        i++;
    }

	return newPointer;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
	print_regs();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
