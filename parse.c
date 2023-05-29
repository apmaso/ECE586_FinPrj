#include "header.h"

int mem_img2bin(char myString[10], int num[SIZ]){
	
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	for(int i=0;i<8;++i){
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

		if(myString[i]=='0'){
			num[a]=0;
			num[b]=0;
			num[c]=0;
			num[d]=0;
		}
		if(myString[i]=='1'){
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
	//prt32(num); //TODO: KEEP THIS HERE FOR FUTURE DEBUGGING.
	return 0;
}//close mem_img2bin function


void parse(struct instruction *an_instruction, int num[SIZ]){

	an_instruction->opcode=extract_opcode(num, OPLEN);
	printf("opcode= %d\n", an_instruction->opcode);
	strcpy(an_instruction->opcode_name,extract_opcode_str(an_instruction->opcode));
	
	an_instruction->rs=extract_rs(num);
	printf("RS is: %d\n", an_instruction->rs);
	an_instruction->rt=extract_rt(num);
	printf("rt is: %d\n", an_instruction->rt);
	an_instruction->rd=extract_rd(num);
	printf("rd is: %d\n", an_instruction->rd);
	an_instruction->imm=extract_immediate(num);
	printf("imm is: %d\n", an_instruction->imm);
	an_instruction->TYPE=extract_type(num);
	printf("type is %d\n", an_instruction->TYPE);
	//printf("type is: %d\n", an_instruction.TYPE);
	an_instruction->ready=0;
}

void fill_mem(int data_seg[], int num[SIZ], int linect){
	//printf("linect is: %d\n", linect);//TODO KEEP FOR DEBUGGING?
	//printf("num is: \n");//TODO: KEEP FOR DEBUGGING?
	//prt32(num);//TODO:KEEP FOR DEBUGGING?
	data_seg[linect]=extract_mem(num);	
	
	//printf("              data_seg is: %d\n", data_seg[linect]);//TODO:KEEP FOR DEBUGGING?
}

void test_mem(int data_seg[], int datact){
	for(int i=0;i<datact;i++){
		printf("%d=i;  data_seg is: %d\n", i, data_seg[i]);
	}
}

int get_mem(int data_seg[], int value){
	int line=value*4;
	printf("line is: %d\n", line);

	return line;
}
void prt32(int num[SIZ]){//TODO: THIS IS FOR DEBUGGING, mostly unused.

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

		printf("\n");
}



