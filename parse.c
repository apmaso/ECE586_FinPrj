#include "header.h"

int hex2bin(char myString[10], int num[SIZ]);
int makearr(char letter, int i_val, int num[SIZ]);
int tst(char myString[10], int num[SIZ]);
void prt32(int num[SIZ]);


int main() {
	char myString[10];
	FILE *fptr;

	char letter = 'Z';
	int i_val = 99;

	int num[SIZ];
	
	fptr = fopen("imageSHORT.txt", "r");
/*	
	for(int i=0;i<5;++i){	
	fgets(myString, 10, fptr);
	//myString <<	
	printf("%s", myString);
	hex2bin(myString);
	}
*/
	while(fgets(myString, 10, fptr)){
		//printf("%s", myString);
		//hex2bin(myString, num);
		tst(myString, num);
	}

	fclose(fptr);

	exit(EXIT_SUCCESS);
}//end of main function.



int tst(char myString[10], int num[SIZ]){
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


	
//		if(myString[i]==1){

	}//close forloop
	prt32(num);

}//close tst function

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
	 printf("\n");
	 }

int eval_opcode(char myString){
	//if(myString[0]==0&&
	
	return 0;
			}


int hex2bin(char myString[10], int num[SIZ]){
	//correct this because there's no leading 0X.
	size_t i = (myString[1] == 'x' || myString[1] == 'X')? 2: 0;
	
	while(myString[i]) {
	//for(int i=0;i<9;++i){
		switch (myString[i]) {
		case '0':
		printf("0000 ");
		makearr('0', i, num);
		break;

		case '1':
		printf("0001 ");
		makearr('1', i, num);
		break;

		case '2':
		printf("0010 ");
		makearr('2', i, num);
		break;

		case '3':
		printf("0011 ");
		makearr('3', i, num);
		break;

		case '4':
		printf("0100 ");
		makearr('4', i, num);

		break;

		case '5':
		printf("0101 ");
		makearr('5', i, num);
		break;

		case '6':
		printf("0110 ");
		makearr('6', i, num);
		break;

		case '7':
		printf("0111 ");
		makearr('7', i, num);
		break;

		case '8':
		printf("1000 ");
		makearr('8', i, num);
		break;

		case '9':
		printf("1001 ");
		makearr('9', i, num);
		break;

		case 'A':
		case 'a':
		printf("1010 ");
		makearr('A', i, num);
		break;

		case 'B':
		case 'b':
		printf("1011 ");
		makearr('B', i, num);
		break;

		case 'C':
		case 'c':
		printf("1100 ");
		makearr('C', i, num);
		break;

		case 'D':
		case 'd':
		printf("1101 ");
		makearr('D', i, num);
		break;

		case 'E':
		case 'e':
		printf("1110 ");
		makearr('E', i, num);
		break;

		case 'F':
		case 'f':
		printf("1111 ");
		makearr('F', i, num);
		break;

		case '/':
		++i;
		printf("\n");
		//++i;
		break;


		default:
		printf("\n");
		//printf("\nInvalid hexadecimal digit %c", myString[i]);
		}//end of switch statement.
		++i;
		printf("i is %ld\n", i);
		if(i==9){
			printf("\n");
			for(int k=0;k<32;++k){
			printf("%d", num[k]);
			}
			printf("\n");
		}

	}//end of for loop.

}//end of hex2bin function.

int makearr(char letter, int i_val, int num[SIZ]){
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	if(i_val=1){
		a=0;
		b=1;
		c=2;
		d=3;
	}
	if(i_val=2){
		a=4;
		b=5;
		c=6;
		d=7;
	}
	if(i_val=3){
		a=8;
		b=9;
		c=10;
		d=11;
	}
	if(i_val=4){
		a=12;
		b=13;
		c=14;
		d=15;
	}
	if(i_val=5){
		a=16;
		b=17;
		c=18;
		d=19;
	}
	if(i_val=6){
		a=20;
		b=21;
		c=22;
		d=23;
	}
	if(i_val=7){
		a=24;
		b=25;
		c=26;
		d=27;
	}
	if(i_val=8){
		a=28;
		b=29;
		c=30;
		d=31;
	}


	if(letter=='0'){
			num[a]=0;
			num[b]=0;
			num[c]=0;
			num[d]=0;
	}
	if(letter =='1'){
			num[a]=0;
			num[b]=0;
			num[c]=0;
			num[d]=1;
	}
	if(letter =='2'){
			num[a]=0;
			num[b]=0;
			num[c]=1;
			num[d]=0;
	}
	if(letter =='3'){
			num[a]=0;
			num[b]=0;
			num[c]=1;
			num[d]=1;
	}
	if(letter =='4'){
			num[a]=0;
			num[b]=1;
			num[c]=0;
			num[d]=0;
	}
	if(letter =='5'){
			num[a]=0;
			num[b]=1;
			num[c]=0;
			num[d]=1;
	}
	if(letter =='6'){
			num[a]=0;
			num[b]=1;
			num[c]=1;
			num[d]=0;
	}
	if(letter =='7'){
			num[a]=0;
			num[b]=1;
			num[c]=1;
			num[d]=1;
	}
	if(letter =='8'){
			num[a]=1;
			num[b]=0;
			num[c]=0;
			num[d]=0;
	}
	if(letter =='9'){
			num[a]=1;
			num[b]=0;
			num[c]=0;
			num[d]=1;
	}
	if(letter =='A'){
			num[a]=1;
			num[b]=0;
			num[c]=1;
			num[d]=0;
	}
	if(letter =='B'){
			num[a]=1;
			num[b]=0;
			num[c]=1;
			num[d]=1;
	}
	if(letter =='C'){
			num[a]=1;
			num[b]=1;
			num[c]=0;
			num[d]=0;
	}
	if(letter =='D'){
			num[a]=1;
			num[b]=1;
			num[c]=0;
			num[d]=1;
	}
	if(letter =='E'){
			num[a]=1;
			num[b]=1;
			num[c]=1;
			num[d]=0;
	}
	if(letter =='F'){
			num[a]=1;
			num[b]=1;
			num[c]=1;
			num[d]=1;
	}

	return 0;
}




















