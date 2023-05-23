#include "header.h"

int hex2bin(char myString[10], int num[SIZ]);
int bin2dec(int array[], int len);
int bin2dec_2sComp(int array[], int len);
int parse(char myString[10], int num[SIZ]);
int opSwitch(int decOp, int rType, int iType);
void prt32(int num[SIZ]);

int main() {
	char myString[10];
	FILE *fptr;

	char letter = 'Z';
	int i_val = 99;

	int num[SIZ];

    int opcode[6];
    int decOp = 0;
    int opLen = 6;

    int rType = 0;
    int iType = 0;

	fptr = fopen("imageSHORT.txt", "r");

	while(fgets(myString, 10, fptr)){
		//printf("%s", myString);
		//hex2bin(myString, num);
		parse(myString, num);

        for (int i=0; i<6; i++){
            opcode[i] = num[(i)];
        }

        decOp = bin2dec(opcode, opLen);
        printf("The decimal value for opcode = %d  ==> ", decOp);
        opSwitch(decOp, rType, iType);
    }

    printf("Total number of R-Type Instructions = %d \n", rType);
    printf("Total number of I-Type Instructions = %d \n", iType);
	
    fclose(fptr);

	exit(EXIT_SUCCESS);
}//end of main function.



int parse(char myString[10], int num[SIZ]){
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
	prt32(num);
	return 0;
}//close parse function

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
		//printf("\n"); Removed new line since I have on after opcode printf.  Just testing functionality
}

int opSwitch(decOp, rType, iType){
    
    switch(decOp){
        case 0:
            printf(" ADD \n");
            ++rType;
            break;

        case 1:
            printf(" ADDI \n");
            ++iType;
            break;
    
        case 2:
            printf(" SUB \n");
            ++rType;
            break;

        case 3:
            printf(" SUBI \n");
            ++iType;
            break;
    
        case 4:
            printf(" MUL \n");
            ++rType;
            break;

        case 5:
            printf(" MULI \n");
            ++iType;
            break;
    
        case 6:
            printf(" OR \n");
            ++rType;
            break;

        case 7:
            printf(" ORI \n");
            ++iType;
            break;
    
        case 8:
            printf(" AND \n");
            ++rType;
            break;

        case 9:
            printf(" ANDI \n");
            ++iType;
            break;

        case 10:
            printf(" XOR \n");
            ++rType;
            break;

        case 11:
            printf(" XORI \n");
            ++iType;
            break;
    
        case 12:
            printf(" LDW \n");
            ++iType;
            break;
    
        case 13:
            printf(" STW \n");
            ++iType;
            break;
    
        case 14:
            printf(" BZ \n");
            ++iType;
            break;
    
        case 15:
            printf(" BEQ \n");
            ++iType;
            break;
    
        case 16:
            printf(" JR \n");
            ++iType;
            break;
    
        case 17:
            printf(" HALT \n");
            ++iType;
            break;
    
    return 0;
    } //end of switch statement
} //end of function

/*
    int opcode[] = {1, 0, 1, 0, 1, 0};
    int decOp = 0;
    int decLen = 6;

    int Rs[] = {1, 0, 1, 0, 1};
    int decRs = 0;
    int RsLen = 5;
	
    int Rt[] = {0, 0, 0, 1, 1};
    int decRt = 0;
    int RtLen = 5;

    int imm[] = {1, 1, 1, 1, 0};
    int decImm = 0;
    int immLen = 5;


    decOp = bin2dec(opcode, opLen);
    decRs = bin2dec(Rs, RsLen);
    decRt = bin2dec(Rt, RtLen);
    decImm = bin2dec_2sComp(imm, immLen);


    printf("The decimal value for opcode = %d \n", decOp);
    printf("The decimal value for Rs = %d \n", decRs);
    printf("The decimal value for Rt = %d \n", decRt);
    printf("The decimal value for Imm = %d \n", decImm);
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
