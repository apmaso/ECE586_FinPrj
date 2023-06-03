#include "header.h"

struct statistics {
	int itype;
	int rtype;
};

struct statistics mystats;

struct instruction program[100]; 
struct instruction pipeline[5];

//program counter:
int pc=0;

//data segment:
int data_seg[1000];
int data_red[1000];

//registers:
int gpReg[32];
int reg_ready[32];


int pipeline_head;  //head->always points to the function that's in the status of fetch; NEEDS to be initialized to zero.
int pipeline_tail;  //tail->always points to the function that's in the status of write_back;  NEEDS to be initialized to zero.
int cycle;

void shift(int opcode, int Rs, int Rt, int Rd, int Imm); 

int main() {
	initialize_pipe();
	char myString[10];
	FILE *fptr;
	int num[SIZ];
	pipeline_head = 0;
	pipeline_tail = 0;
	int linect = 0;//maintain a count of the lines as we step through the file.
	int progstop = 0;//this is the last line of the program portion of the file. 
	initialize_reg(gpReg);

	fptr = fopen("TEST2.txt", "r");
	//imageAddTB.txt
	//FIXME line83, pass the name of the file as a variable. i.e. arg1.
	//FIXME PUT This loop into a function, fillprogram

	progstop = process_program(myString, fptr, linect, progstop, num, &program);
	while(fgets(myString, 10, fptr)){

		mem_img2bin(myString, num);
		fill_mem(data_seg, num, linect++);
	}
	print_program(progstop);

	//test_mem(data_seg, linect);
	//printf("linect is: %d\n", linect);
	fclose(fptr);

	//testing/proving:
	//print_reg(gpReg);

	//int encounter_halt=0;
		for(;;){
		//int end_program=0;

		if(check_for_halt()==1)
			break;
		cycle++;
		cleanup_pipe();	
		//write_back: just move it to write back stage from memory.
		printf("Cycle: %d____________________________________________________________\n", cycle);
		write_back();

		//mem-access, if load or store, there is a memory operation. otherwise just move it forward, probably. 
		memory_access();
		//execute's the program.
		execute_instruction();

		//decode an instruction from the program array, unless there is a stall.
		decode_instruction();

		//fetch an instruction from the program array, unless there's a stall.

		fetch_instruction(&pc);

		//decode an instruction from the program array, unless there is a stall.

		//pc++;//increment program counter by one.  (need to adjust to four later).	
	}
	/*	
		for(int i=0;i<progstop;i++){
	//for(int j=0;j<5;j++){
	//change the name of this function assignment->to something else.
	//copy_to_pipe(&program[i], &pipeline[j]);
	display_struct(&pipeline[i]);
	//}			
	//process_code(&program[i], gpReg);
	}
	//print_reg(gpReg);//prints the list of registers.
	*/	
	/*
	   for(int i=0;i<5;i++){
	   display_struct(&pipeline[i]);
	   }
	   */

	exit(EXIT_SUCCESS);
}//end of main function.

void initialize_array(struct instruction *an_instruction[]){

	for(int i=0;i<5;i++){
		pipeline[i].pipe_stage=-1;
	}
}


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

int extract_mem(int bin_inst[]){
	int mem[32];
	int dec_mem=0;

	for(int i=0;i<32;i++){
		mem[i]=bin_inst[(i)];
	}
	dec_mem=bin2dec(mem, 32);
	return dec_mem;
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
	printf("RS is: %d ", dec_rs);
	return dec_rs;
}

int extract_rt(int bin_inst[]){

	int rt[5];
	int dec_rt = 0;

	for (int i=11, j=0; i<16;i++){
		rt[j++]=bin_inst[(i)];
	}

	dec_rt = bin2dec(rt, 5);
	printf("RT is: %d ", dec_rt);
	return dec_rt;
}

int extract_rd(int bin_inst[]){

	int rd[5];
	int dec_rd = 0;

	for (int i=16, j=0; i<21;i++){
		rd[j++]=bin_inst[(i)];
	}

	dec_rd = bin2dec(rd, 5);
	printf("RD is: %d\n", dec_rd);
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
	//printf("linecount is %d\n", linect);
	for(int i=0;i<linect;i++){
		if(program[i].TYPE==0) //THIS IS R-TYPE
			printf("%s R%d, R%d R%d \n", program[i].opcode_name, program[i].rd, program[i].rs, program[i].rt);

		if(program[i].TYPE==1) //THIS IS i-TYPE
			printf("%s R%d, R%d %d \n", program[i].opcode_name, program[i].rt, program[i].rs, program[i].imm);
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



int process_program(char myString[], FILE *fptr, int linect, int progstop,int num[], struct instruction *an_instruction[]){
	//TODO:Need to test this function, only compiles, has not been tested.
	while(fgets(myString, 10, fptr)){
		mem_img2bin(myString, num);//converts hex to bin, saves in num.
					   //prt32(num);//prints all 32 bits of the binary number (TODO for testing)
		parse(&program[linect++], num);
		if(program[linect-1].opcode==17){//this is a halt instruction
						 //continue filling the memory, stop filling the program.	
			progstop=linect;
			return progstop;
			//break;	
		}
	}
	return progstop;
}

int  pipe_empty() {

	int i=-3;
	for(i=0;i<5;i++)
		if(pipeline[i].pipe_stage==-1)
			break;
	return i;

}
void fetch_instruction(int *pc){

	int fetched_inst_stage = stagebusy(0);

	if (fetched_inst_stage == -1 || *pc == 1) {

		int empty_pipe_slot=pipe_empty();

		copy_to_pipe(&program[*pc], &pipeline[empty_pipe_slot]);
		pipeline[empty_pipe_slot].pipe_stage=0; 
		//branch needs different handling.
		(*pc)++;

		printf("\nFetching inst.");
		display_struct(&pipeline[empty_pipe_slot]);
	}

	printf("exiting fetch.\n");
}



void decode_instruction() {

	int fetched_inst_index=stagebusy(0);

	if(stagebusy(1)==-1 && fetched_inst_index != -1) {
	
		//FIXME: on Branch a stall might happen
		//pipeline[fetched_inst_index].pipe_stage=1;

		if(pipeline[fetched_inst_index].opcode==12 && cycle>reg_ready[pipeline[fetched_inst_index].rs]; /*&& no store with same address is pending*/ ){//type 1.
					
			reg_ready[pipeline[fetched_inst_index].rt]=cycle+2;
			pipeline[fetched_inst_index].pipe_stage=1;
		}
		else if(pipeline[fetched_inst_index].opcode==13 && cycle>reg_ready[pipeline[fetched_inst_index].rs]){
				
			int effective_address=gpReg[pipeline[fetched_inst_index].rs]+pipeline[fetched_inst_index].imm;
			//FIXME address conflicts need to be resolved.
			data_red[effective_address]=reg_ready[pipeline[fetched_inst_index].rs]+2;
		}
		else{
			pipeline[fetched_inst_index].pipe_stage=1;
		}

		printf("\nDecoding inst.");
		display_struct(&pipeline[fetched_inst_index]);
	}
	
	printf("exiting decode.\n");
}

void execute_instruction(){
		
		//execute the actual code...
		int decoded_inst_index=stagebusy(1);
		if(stagebusy(2)==-1 && decoded_inst_index != -1){

				if(pipeline[decoded_inst_index].TYPE==0) {

					if(cycle>reg_ready[pipeline[decoded_inst_index].rs] && cycle>reg_ready[pipeline[decoded_inst_index].rt]){

						pipeline[decoded_inst_index].pipe_stage=2;
						reg_ready[pipeline[decoded_inst_index].rd]=cycle+2;
						
						printf("execute inst.");
						display_struct(&pipeline[decoded_inst_index]);

					}		
					else printf("STALL:execute inst. \n");
				}

				if(pipeline[decoded_inst_index].TYPE==1) {

					if(cycle>reg_ready[pipeline[decoded_inst_index].rs]) {
						pipeline[decoded_inst_index].pipe_stage=2;//update execution stage of instruction in pipe.
						reg_ready[pipeline[decoded_inst_index].rt]=cycle+2;
						
						printf("execute inst.");
						display_struct(&pipeline[decoded_inst_index]);

					}
					else printf("STALL:execute inst. \n");
				}
		
		//print_reg(reg_ready);//register print - for debugging.

		}
		
		printf("exiting execute.\n");
	}//closes execute 



void memory_access(){

	int executed_inst_index=stagebusy(2);
	if(stagebusy(3) == -1 && executed_inst_index != -1){

		pipeline[executed_inst_index].pipe_stage=3;
			if(pipeline[executed_inst_index].opcode==12 /*&& no store with same address is pending*/ ){//type 1.
					
				reg_ready[pipeline[executed_inst_index].rt]=cycle+2;
			}
			else if(pipeline[executed_inst_index].opcode==13){
				
//int gpReg[32];
				int effective_address=gpReg[pipeline[executed_inst_index].rs]+pipeline[executed_inst_index].imm;
				//FIXME address conflicts need to be resolved.
				data_red[effective_address]=reg_ready[pipeline[executed_inst_index].rs]+2;
//int data_red[1000];
			}
			//execution will have calculated address.
			//here, you will update the shadow array of memory to be the cycle+1;
			//need to calculate an address, is all instructions move into this stage.
			//grab the executed one, make it memory, whatever we did before, put in memory,
			//check if load or store (do a bunch of stuff) 
			//move the index returned to us to be memory, after that we'll know if it's load or store,
			//we'll do a bunch of stuff, then we exit.  
			//execute memory access function.
			printf("mem inst.");	
			display_struct(&pipeline[executed_inst_index]);
		}

		printf("exiting mem-access.\n");
	}


	void write_back(){

		int mem_inst_index=stagebusy(3);
		if(stagebusy(4)== -1 && mem_inst_index != -1){

			pipeline[mem_inst_index].pipe_stage=4;
			printf("write_Back inst.");
			display_struct(&pipeline[mem_inst_index]);
		}

		printf("exiting WB.\n");
		//display_struct(&pipeline[mem_inst_index]);
		
	}


int stagebusy(int execution_stage){//this function is very confusing.

		//if the stage is busy return the index of that entry else return -1
		int stage_busy=-1;
		for(int i=0;i<5;i++){

			if(pipeline[i].pipe_stage==-1)//if pipeline is initialized to all -1s, the else if never runs.
				continue;
			else if(pipeline[i].pipe_stage==execution_stage){
				return i;
			}
		}	
		return stage_busy;//this will execute only for -1

}

void cleanup_pipe(){
		//loop over the pipeline:
		for(int i=0;i<5;i++){
			if(pipeline[i].pipe_stage==4) {
				printf("inside the cleanup\n");
				pipeline[i].pipe_stage=-1;

			}
		}
	}

int check_for_halt() {

		for(int i=0;i<5;i++){
			if(pipeline[i].pipe_stage==4 && pipeline[i].opcode==17)
				return 1;
		}
		return 0;

	}


	void initialize_pipe(){

		for(int i=0;i<5;i++){
			pipeline[i].opcode = -1;
			pipeline[i].rs= -1;
			pipeline[i].rt= -1;
			pipeline[i].rd= -1;
			pipeline[i].imm= -1;
			pipeline[i].ready= -1;
			pipeline[i].pipe_stage = -1;

		}
	}
