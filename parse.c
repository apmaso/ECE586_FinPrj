#include "header.h"
//#include <stdio.h>
//#include <stdlib.h>

int hex2bin(char myString[10], int num[SIZ]);

int main() {
	char myString[10];
	FILE *fptr;

	int arr1[3];
	int arr2[3];
	int arr3[3];
	int arr4[3];
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
		hex2bin(myString, num);
	}

	fclose(fptr);

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
