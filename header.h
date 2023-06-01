//ECE586.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "instruction.h"

#define SIZ 32
#define OPLEN 6
#define REGLEN 5
#define IMMLEN 16 



int process_program(char myString[], FILE *fptr, int linect, int progstop,int num[], struct instruction *an_instruction[]);
void print_inst(struct instruction);
struct instruction fill_instruction(int bin_inst[], int len);
int hex2bin(char myString[10], int num[SIZ]);
int bin2dec(int array[], int len);
int bin2dec_2sComp(int array[], int len);
int mem_img2bin(char myString[10], int num[SIZ]);
void opSwitch(int decOp);
void prt32(int num[SIZ]);
int extract_opcode(int bin_inst[], int opLen);
int extract_rs(int bin_inst[]);
int extract_rt(int bin_inst[]);
int extract_rd(int bin_inst[]);
int extract_immediate(int bin_inst[]);
int extract_type(int bin_inst[]);
int extract_mem(int bin_inst[]);
void print_program(int linect);
const char *extract_opcode_str(int opcode);
void parse(struct instruction *an_instruction, int num[SIZ]);
void fill_mem(int data_seg[], int num[SIZ], int datact);
void test_mem(int data_seg[], int linect);

void initialize_reg(int gpReg[32]);
int process_code(struct instruction *an_instruction, int gpReg[]);
int ADD(int rs, int rt);
int ADDI(int rs, int imm);
void print_reg(int gpReg[]);


void assignment(struct instruction *an_instruction, struct instruction *other_instruction);
void display_struct(struct instruction *an_instruction);


void fetch_instruction(int pc );
void decode_instruction();
void execute_instruction();
void memory_access();
void write_back();




