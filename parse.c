#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int hex2bin(char myString[10], int num[SIZ]);
int bin2dec(int opcode[], int len);
int bin2dec_2sComp(int opcode[], int len);


int main() {
	char myString[10];
	FILE *fptr;

	int arr1[3];
	int arr2[3];
	int arr3[3];
	int arr4[3];
	int num[SIZ];


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
		hex2bin(myString, num);
	}



    fclose(fptr);


    decOp = bin2dec(opcode, decLen);
    decRs = bin2dec(Rs, RsLen);
    decRt = bin2dec(Rt, RtLen);
    decImm = bin2dec_2sComp(imm, immLen);


    printf("The decimal value for opcode = %d \n", decOp);
    printf("The decimal value for Rs = %d \n", decRs);
    printf("The decimal value for Rt = %d \n", decRt);
    printf("The decimal value for Imm = %d \n", decImm);


	exit(EXIT_SUCCESS);
}//end of main function.

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
		break;

		case '1':
		printf("0001 ");
		break;

		case '2':
		printf("0010 ");
		break;

		case '3':
		printf("0011 ");
		break;

		case '4':
		printf("0100 ");
		break;

		case '5':
		printf("0101 ");
		break;

		case '6':
		printf("0110 ");
		break;

		case '7':
		printf("0111 ");
		break;

		case '8':
		printf("1000 ");
		break;

		case '9':
		printf("1001 ");
		break;

		case 'A':
		case 'a':
		printf("1010 ");
		break;

		case 'B':
		case 'b':
		printf("1011 ");
		break;

		case 'C':
		case 'c':
		printf("1100 ");
		break;

		case 'D':
		case 'd':
		printf("1101 ");
		break;

		case 'E':
		case 'e':
		printf("1110 ");
		break;

		case 'F':
		case 'f':
		printf("1111 ");
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
	}//end of for loop.

}//end of hex2bin function.

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
