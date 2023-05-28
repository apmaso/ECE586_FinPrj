
#include "header.h"

struct statistics {
	int itype;
	int rtype;
};

struct statistics mystats;

struct instruction program[3000]; //TODO FIXME

void shift(int opcode, int Rs, int Rt, int Rd, int Imm); 

int main() {
	char myString[10];
	FILE *fptr;
	int num[SIZ];

	int linect = 0;
	//initialize_program();
	fptr = fopen("image.txt", "r");

	//FIXME line83, pass the name of the file as a variable. i.e. arg1.
	while(fgets(myString, 10, fptr)){
		mem_img2bin(myString, num);
		//prt32(num);
		parse(&program[linect++], num);
		if(program[linect-1].opcode==17){//this is a halt instruction
						 //continue filling the memory, stop filling the program.	
			break;	
		}
	}
	print_program(linect);

	fclose(fptr);

	exit(EXIT_SUCCESS);
}//end of main function.


int bin1dec_2sComp(int array[], int len) {

	// Decimal value to be returned
	int dec = 0;

	for (int i=0; i< len; i++) {
		if (array[i] == 1) {
			dec = (dec + pow(2, (len-1-i)));
		}
	}

	if (array[0] == 1) {
		dec = (dec - pow(2, (len)));
	}
	//return decimal value;  
	return dec; 
}//end of bin2dec_2sComp

int bin2dec(int array[], int len) {

	// Decimal value to be returned
	int dec = 0;


	for (int i=0; i< len; i++) {
		if (array[i] == 1) {
			dec = (dec + pow(2, (len-1-i)));
		}
	}
	//return decimal value;  
	return dec;  
}//end of bin2dec
 //

int extract_opcode(int bin_inst[], int opLen){

	int opcode[6];
	int decOp = 0;

	for (int i=0; i<6; i++){
		opcode[i] = bin_inst[(i)];
	}   

	decOp = bin2dec(opcode, opLen);
	return decOp;
}

const char* extract_opcode_str(int opcode){
	int op=opcode;
	//char inst_str[5];
	if(op==0)
		//strcpy(inst_str, "ADD");
		return "ADD";

	if(op==1)
		//strcpy(inst_str, "ADDI");
		return "ADDI";
	if(op==2)
		//strcpy(inst_str, "SUB");
		return "SUB";
	if(op==3)
		return "SUBI";
	if(op==4)
		return "MUL";
	if(op==5)
		return "MULI";
	if(op==6)
		return "OR";
	if(op==7)
		return "ORI";
	if(op==8)
		return "AND";
	if(op==9)
		return "ANDI";
	if(op==10)
		return "XOR";
	if(op==11)
		return "XORI";
	if(op==12)
		return "LDW";
	if(op==13)
		return "STW";
	if(op==14)
		return "BZ";
	if(op==15)
		return "BEQ";
	if(op==16)
		return "JR";
	if(op==17)
		return "HALT";
	else
		return "XXXX";
}

int extract_rs(int bin_inst[]){

	int rs[5];
	int dec_rs = 0;

	for (int i=6, j=0; i<11;i++){
		rs[j++]=bin_inst[(i)];
	}

	dec_rs = bin2dec(rs, 5);
	return dec_rs;
}

int extract_rt(int bin_inst[]){

	int rt[5];
	int dec_rt = 0;

	for (int i=11, j=0; i<16;i++){
		rt[j++]=bin_inst[(i)];
	}

	dec_rt = bin2dec(rt, 5);

	return dec_rt;
}

int extract_rd(int bin_inst[]){

	int rd[5];
	int dec_rd = 0;

	for (int i=21, j=0; i<26;i++){
		rd[j++]=bin_inst[(i)];
	}

	dec_rd = bin2dec(rd, 5);

	return dec_rd;
}

int extract_type(int bin_inst[]){

	int decimal_opcode = extract_opcode(bin_inst, 6);

	if(decimal_opcode == 0 || decimal_opcode == 2 || decimal_opcode ==4 || decimal_opcode==6 || decimal_opcode==8 || decimal_opcode==10){
		//0 = ADD; 2=SUB; 4=MUL; 6= 8=AND 10=XOR.
		return 0;
	}
	else
		return 1;
}

int extract_immediate(int bin_inst[]){

	int imm[16];
	int dec_imm = 0;

	for(int i=16, j=0; i<32;i++){
		imm[j++]=bin_inst[(i)];
	}
	dec_imm=bin1dec_2sComp(imm, 16);

	return dec_imm;
}

void print_program(int linect){
	printf("linecount is %d\n", linect);
	for(int i=0;i<linect;i++){
		if(program[i].TYPE==0)
			printf("%s R%d, R%d R%d \n", program[i].opcode_name, program[i].rs, program[i].rt, program[i].rd);

		if(program[i].TYPE==1)
			printf("%s R%d, R%d %d \n", program[i].opcode_name, program[i].rs, program[i].rt, program[i].imm);
	}
}

struct instruction fill_instruction(int bin_inst[], int len){

	struct instruction my_instruct;
	my_instruct.opcode = extract_opcode(bin_inst, 6);  //bin2dec(opcode, len);
	my_instruct.rs = extract_rs(bin_inst);
	my_instruct.rt = extract_rt(bin_inst);
	my_instruct.rd = extract_rd(bin_inst);
	my_instruct.TYPE = extract_type(bin_inst);

	my_instruct.ready = 0;
	return my_instruct;
}









