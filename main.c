#include "header.h"

struct statistics {
	int itype;
	int rtype;
};

struct statistics mystats;

/*
struct instruction {
	int opcode;
	int Rs;
	int Rt;
	// Rd = -1 indicates itype instruction
	int Rd;
	int Imm;
};
*/

struct instruction inst1;
struct instruction inst2;
struct instruction inst3;
struct instruction inst4;
struct instruction inst5;

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
void print_program(int linect);
const char *extract_opcode_str(int opcode);
struct instruction parse(int num[SIZ]);

struct instruction program[500]; //TODO FIXME

void shift(int opcode, int Rs, int Rt, int Rd, int Imm); 

int main() {
	struct instruction instr;
	char myString[10];
	FILE *fptr;
	int num[SIZ];

	/*
	char letter = 'Z';
	int i_val = 99;

	int opcode[6];
	int decOp = 0;

	int binRs[5];
	int decRs = 0;

	int binRt[5];
	int decRt = 0;

	int binRd[5];
	int decRd = 0;

	int binImm[16];
	int decImm = 0;

	int rType = 0;
	int iType = 0;

	mystats.itype = 0;
	mystats.rtype = 0;
*/
	int linect = 0;
	fptr = fopen("imageShort2.txt", "r");
//FIXME line83, pass the name of the file as a variable. i.e. arg1.
	while(fgets(myString, 10, fptr)){
		//printf("%s", myString);
		//hex2bin(myString, num);
		mem_img2bin(myString, num);
		program[linect++]=parse(num);
		//struct instruction an_instruction=parse(num);
		/*
		// parse and decode the opcode
		for (int i=0; i<6; i++){
			opcode[i] = num[i];
		}
		decOp = bin2dec(opcode, OPLEN);
		//printf("| Opcode: ");
		opSwitch(decOp);
		printf("\n");
		//print_stuff(num);
		*/
		/*
		// parse and decode the source register, Rs
		for (int j=0; j<5; j++){
		binRs[j] = num[j+6];
		}
		decRs = bin2dec(binRs, REGLEN);
		printf("| Rs = R%d", decRs);

		// parse and decode the target register, Rt
		for (int k=0; k<5; k++){
		binRt[k] = num[k+11];
		}
		decRt = bin2dec(binRt, REGLEN);
		printf(" | Rt = R%d", decRt);

		// Is the instruction rtype?
		if ((decOp % 2 == 0) && (decOp < 11)) {

		// parse and decode the destination register, Rd
		for (int l=0; l<5; l++){
		binRd[l] = num[l+16];
		}
		decRd = bin2dec(binRd, REGLEN);
		printf(" | Rd = R%d \n", decRd);

		// shift register for rtype (Imm = 0)
		shift(decOp, decRs, decRt, decRd, 0);
		}
		// If instruction isn't rtype, then its itype
		else {

		// parse and decode the immediate value
		for (int m=0; m<16; m++){
		binImm[m] = num[m+16];
		}
		decImm = bin2dec(binImm, IMMLEN);
		printf(" | Imm = %d \n", decImm);

		// shift register for itype (Rd = -1)
		shift(decOp, decRs, decRt, 0, decImm);
		}
		*/
		print_program(linect);
	}
	//printf("Total number of R-Type Instructions = %d \n", mystats.rtype);
	//printf("Total number of I-Type Instructions = %d \n", mystats.itype);
	//printf("The last instruction had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst1.opcode, inst1.Rs, inst1.Rt, inst1.Rd, inst1.Imm);
	//printf("The instruction before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst2.opcode, inst2.Rs, inst2.Rt, inst2.Rd, inst2.Imm);
	//printf("The instruction 2 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst3.opcode, inst3.Rs, inst3.Rt, inst3.Rd, inst3.Imm);
	//printf("The instruction 3 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst4.opcode, inst4.Rs, inst4.Rt, inst4.Rd, inst4.Imm);
	//printf("The instruction 4 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst5.opcode, inst5.Rs, inst5.Rt, inst5.Rd, inst5.Imm);


	fclose(fptr);

	exit(EXIT_SUCCESS);
}//end of main function.

int mem_img2bin(char myString[10], int num[SIZ]){
	//printf("test\n");
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	for(int i=0;i<8;++i){
		//printf("i is: %d\n", i);
		if(i==0){
			a=0;
			b=1;
			c=2;
			d=3;
		}
		if(i==1){
			a=4;
			b=5;
			c=6;
			d=7;
		}
		if(i==2){
			a=8;
			b=9;
			c=10;
			d=11;
		}
		if(i==3){
			a=12;
			b=13;
			c=14;
			d=15;
		}
		if(i==4){
			a=16;
			b=17;
			c=18;
			d=19;
		}
		if(i==5){
			a=20;
			b=21;
			c=22;
			d=23;
		}
		if(i==6){
			a=24;
			b=25;
			c=26;
			d=27;
		}
		if(i==7){
			a=28;
			b=29;
			c=30;
			d=31;
		}

		//printf("mystring[i] is: %c, %d\n", myString[i], i);
		//printf("mystring is: %s\n", myString);

		if(myString[i]=='0'){
			//printf("mystring[i] is: %c\n", myString[i]);
			num[a]=0;
			num[b]=0;
			num[c]=0;
			num[d]=0;
		}
		if(myString[i]=='1'){
			//printf("mystring[i] is: %c\n", myString[i]);
			num[a]=0;
			num[b]=0;
			num[c]=0;
			num[d]=1;
		}
		if(myString[i]=='2'){
			num[a]=0;
			num[b]=0;
			num[c]=1;
			num[d]=0;
		}
		if(myString[i]=='3'){
			num[a]=0;
			num[b]=0;
			num[c]=1;
			num[d]=1;
		}
		if(myString[i]=='4'){
			num[a]=0;
			num[b]=1;
			num[c]=0;
			num[d]=0;
		}
		if(myString[i]=='5'){
			num[a]=0;
			num[b]=1;
			num[c]=0;
			num[d]=1;
		}
		if(myString[i]=='6'){
			num[a]=0;
			num[b]=1;
			num[c]=1;
			num[d]=0;
		}
		if(myString[i]=='7'){
			num[a]=0;
			num[b]=1;
			num[c]=1;
			num[d]=1;
		}
		if(myString[i]=='8'){
			num[a]=1;
			num[b]=0;
			num[c]=0;
			num[d]=0;
		}
		if(myString[i]=='9'){
			num[a]=1;
			num[b]=0;
			num[c]=0;
			num[d]=1;
		}
		if(myString[i]=='A'){
			num[a]=1;
			num[b]=0;
			num[c]=1;
			num[d]=0;
		}
		if(myString[i]=='B'){
			num[a]=1;
			num[b]=0;
			num[c]=1;
			num[d]=1;
		}
		if(myString[i]=='C'){
			num[a]=1;
			num[b]=1;
			num[c]=0;
			num[d]=0;
		}
		if(myString[i]=='D'){
			num[a]=1;
			num[b]=1;
			num[c]=0;
			num[d]=1;
		}
		if(myString[i]=='E'){
			num[a]=1;
			num[b]=1;
			num[c]=1;
			num[d]=0;
		}
		if(myString[i]=='F'){
			num[a]=1;
			num[b]=1;
			num[c]=1;
			num[d]=1;
		}
	}//close forloop
	//prt32(num);
	return 0;
}//close mem_img2bin function


struct instruction parse(int num[SIZ]){
	struct instruction an_instruction;	
	an_instruction.opcode=extract_opcode(num, OPLEN);
	strcpy(an_instruction.opcode_name,extract_opcode_str(an_instruction.opcode));
	an_instruction.rs=extract_rs(num);
	an_instruction.rt=extract_rt(num);
	an_instruction.rd=extract_rd(num);
	an_instruction.imm=extract_immediate(num);
	an_instruction.TYPE=extract_type(num);
	an_instruction.ready=0;


	return an_instruction;
}

void prt32(int num[SIZ]){
	int count = 0;
	for(int i=0;i<32;++i){
		if(count!=3){
			printf("%d", num[i]);
			++count;
		}
		else{
			printf("%d ", num[i]);
			count=0;
		}
	}
}

void opSwitch(int decOp) {

	switch(decOp){
		case 0:
			printf(" ADD  ");
			mystats.rtype++;
			break;

		case 1:
			printf(" ADDI ");
			mystats.itype++;
			break;

		case 2:
			printf(" SUB  ");
			mystats.rtype++;
			break;

		case 3:
			printf(" SUBI ");
			mystats.itype++;
			break;

		case 4:
			printf(" MUL  ");
			mystats.rtype++;
			break;

		case 5:
			printf(" MULI ");
			mystats.itype++;
			break;

		case 6:
			printf(" OR   ");
			mystats.rtype++;
			break;

		case 7:
			printf(" ORI  ");
			mystats.itype++;
			break;

		case 8:
			printf(" AND  ");
			mystats.rtype++;
			break;

		case 9:
			printf(" ANDI ");
			mystats.itype++;
			break;

		case 10:
			printf(" XOR  ");
			mystats.rtype++;
			break;

		case 11:
			printf(" XORI ");
			mystats.itype++;
			break;

		case 12:
			printf(" LDW  ");
			mystats.itype++;
			break;

		case 13:
			printf(" STW  ");
			mystats.itype++;
			break;

		case 14:
			printf(" BZ   ");
			mystats.itype++;
			break;

		case 15:
			printf(" BEQ  ");
			mystats.itype++;
			break;

		case 16:
			printf(" JR   ");
			mystats.itype++;
			break;

		case 17:
			printf(" HALT ");
			mystats.itype++;
			break;
	} //end of switch statement
} //end of function
/*
void shift(int opcode, int Rs, int Rt, int Rd, int Imm) {

	// using assignment to copy entire struct for now... could use memcopy
	// or could also implement with arrays and a true shift register
	inst5 = inst4;
	inst4 = inst3;
	inst3 = inst2;
	inst2 = inst1;
	inst1.opcode = opcode;
	inst1.rs = Rs;
	inst1.rt = Rt;
	inst1.rd = Rd;
	inst1.imm = Imm;

} //end of shift register function 
*/
int bin2dec_2sComp(int array[], int len) {

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

void print_inst(struct instruction instr){
	if(instr.TYPE== 0) {//first one)
			    //printf("%s R%d,K%d")
	}
	else    
		;
	//print the other style
}       

//                      print an assembly add r5, r7
//                      subtract memory address comma.

int extract_opcode(int bin_inst[], int opLen){

	int opcode[6];
	int decOp = 0;

	for (int i=0; i<6; i++){
		opcode[i] = bin_inst[(i)];
	}   

	decOp = bin2dec(opcode, opLen);
	//printf("decOp is: %d\n", decOp);
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
}

	int extract_rs(int bin_inst[]){

		int rs[5];
		int dec_rs = 0;

		for (int i=6, j=0; i<11;i++){
			rs[j++]=bin_inst[(i)];
			//printf("rs[i] is: %d\n", rs[i]);
		}

		dec_rs = bin2dec(rs, 5);
		//printf("decrs is %d\n", dec_rs);

		return dec_rs;
	}

	int extract_rt(int bin_inst[]){

		int rt[5];
		int dec_rt = 0;

		for (int i=11, j=0; i<16;i++){
			rt[j++]=bin_inst[(i)];
		}

		dec_rt = bin2dec(rt, 5);
		//printf("decrt is %d\n", dec_rt);

		return dec_rt;
	}

	int extract_rd(int bin_inst[]){

		int rd[5];
		int dec_rd = 0;

		for (int i=21, j=0; i<26;i++){
			rd[j++]=bin_inst[(i)];
		}

		dec_rd = bin2dec(rd, 5);
		//printf("decrd is %d\n", dec_rd);

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

		for(int i=16, j=0; i<31;i++){
			imm[j++]=bin_inst[(i)];
		}
		dec_imm = bin2dec(imm, 16);
		//printf("imm is: %d\n", dec_imm);

		return dec_imm;
	}

	void print_program(int linect){

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





















