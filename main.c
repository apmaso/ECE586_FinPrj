#include "header.h"

struct statistics {
    int totalInst;
    int itype;
    int rtype;
    int pc;
    int arithmetic;
    int logical;
    int memAccess;
    int ctrlTransfer;
};

struct statistics mystats;

struct instruction {
    int opcode;
    int Rs;
    int Rt;
    int Rd;
    int Imm;
};

struct instruction inst1;
struct instruction inst2;
struct instruction inst3;
struct instruction inst4;
struct instruction inst5;

// Int array for general purpose registers
int GPReg[32];

int hex2bin(char myString[10], int num[SIZ]);
int bin2dec(int array[], int len);
int bin2dec_2sComp(int array[], int len);
int parse(char myString[10], int num[SIZ]);
void opSwitch(int decOp);
void prt32(int num[SIZ]);
void shift(int opcode, int Rs, int Rt, int Rd, int Imm); 

#define OPLEN 6
#define REGLEN 5
#define IMMLEN 16 

int main() {
	char myString[10];
	FILE *fptr;

	int i_val = 99;

	int num[SIZ];

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
    
    mystats.itype = 0;
    mystats.rtype = 0;
    mystats.pc = 0;
    mystats.arithmetic = 0;
    mystats.logical = 0;
    mystats.memAccess = 0;
    mystats.ctrlTransfer = 0;
    mystats.totalInst = 0;

    // Initialize Reg array to 0
    for (int a=0; a<32; a++) {
        GPReg[a] = 0;
    }
    

    fptr = fopen("imageFiles/image.txt", "r");

	while(fgets(myString, 10, fptr)){
		//printf("%s", myString);
		//hex2bin(myString, num);
		parse(myString, num);

        // parse and decode the opcode
        for (int i=0; i<6; i++){
            opcode[i] = num[i];
        }
        decOp = bin2dec(opcode, OPLEN);

        // parse and decode the source register, Rs
        for (int j=0; j<5; j++){
            binRs[j] = num[j+6];
        }
        decRs = bin2dec(binRs, REGLEN);
        
        // parse and decode the target register, Rt
        for (int k=0; k<5; k++){
            binRt[k] = num[k+11];
        }
        decRt = bin2dec(binRt, REGLEN);
    
        // Is the instruction rtype?
        if ((decOp % 2 == 0) && (decOp < 11)) {

            // parse and decode the destination register, Rd
            for (int l=0; l<5; l++){
                binRd[l] = num[l+16];
            }
            decRd = bin2dec(binRd, REGLEN);
            decImm = 0;
        }
        // If instruction isn't rtype, then its itype
        else {
            
            // parse and decode the immediate value
            for (int m=0; m<16; m++){
                binImm[m] = num[m+16];
            }
            decImm = bin2dec_2sComp(binImm, IMMLEN);
            decRd = 0;
        }
    

        // send decoded decimal values to shift register
        shift(decOp, decRs, decRt, decRd, decImm);
        
        // Display Opcode and Call Switch function to execute inst
        printf(" Opcode: ");
        opSwitch(decOp);
       
        // Display Source Register 
        if (decRs<10) {
            printf("| Rs = R%d ", decRs);
        }
        else {
            printf("| Rs = R%d", decRs);
        }
        
        // Display Target Register 
        if (decRt<10) {
            printf("| Rt = R%d ", decRt);
        }
        else {
            printf("| Rt = R%d", decRt);
        }

        // Is the instruction rtype? Then display Rd
        // If not, then display the Imm value
        if ((decOp % 2 == 0) && (decOp < 11)) {
            printf(" | Rd = R%d \n", decRd);
        }
        else {
            printf(" | Imm = %d \n", decImm);
        }
    }
    
    printf("The program counter has a final value of %d \n", mystats.pc);
    printf("Total number of R-Type Instructions = %d \n", mystats.rtype);
    printf("Total number of I-Type Instructions = %d \n", mystats.itype);
    printf("Total number of Arithmetic Instructions = %d \n", mystats.arithmetic);
    printf("Total number of Logical Instructions = %d \n", mystats.logical);
    printf("Total number of Memory Access Instructions = %d \n", mystats.memAccess);
    printf("Total number of Control Transfer Instructions = %d \n", mystats.ctrlTransfer);
    printf("Total number of Instructions = %d \n", mystats.totalInst);
    printf("The last instruction had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst1.opcode, inst1.Rs, inst1.Rt, inst1.Rd, inst1.Imm);
    printf("The instruction before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst2.opcode, inst2.Rs, inst2.Rt, inst2.Rd, inst2.Imm);
    printf("The instruction 2 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst3.opcode, inst3.Rs, inst3.Rt, inst3.Rd, inst3.Imm);
    printf("The instruction 3 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst4.opcode, inst4.Rs, inst4.Rt, inst4.Rd, inst4.Imm);
    printf("The instruction 4 before last had Opcode=%d, Rs=%d, Rt=%d, Rd=%d, Imm=%d \n", inst5.opcode, inst5.Rs, inst5.Rt, inst5.Rd, inst5.Imm);
    
    printf("General Purpose Registers \n");
    for (int b=0; b<32; b++) {
        printf("Register %d = %d | ", b, GPReg[b]);
    
        // print out five register values per line
        if (b%5==0) {
        printf("\n");
        }
    }


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

void opSwitch(int decOp) {
    
    switch(decOp){
        case 0:
            printf(" ADD  ");
            mystats.rtype++;
            mystats.arithmetic++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] + GPReg[inst1.Rt]); 
            break;

        case 1:
            printf(" ADDI ");
            mystats.itype++;
            mystats.arithmetic++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] + inst1.Imm); 
            break;
    
        case 2:
            printf(" SUB  ");
            mystats.rtype++;
            mystats.arithmetic++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] - GPReg[inst1.Rt]); 
            break;

        case 3:
            printf(" SUBI ");
            mystats.itype++;
            mystats.arithmetic++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] - inst1.Imm); 
            break;
    
        case 4:
            printf(" MUL  ");
            mystats.rtype++;
            mystats.arithmetic++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] * GPReg[inst1.Rt]); 
            break;

        case 5:
            printf(" MULI ");
            mystats.itype++;
            mystats.arithmetic++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] * inst1.Imm); 
            break;
    
        case 6:
            printf(" OR   ");
            mystats.rtype++;
            mystats.logical++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] | GPReg[inst1.Rt]); 
            break;

        case 7:
            printf(" ORI  ");
            mystats.itype++;
            mystats.logical++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] | inst1.Imm); 
            break;
    
        case 8:
            printf(" AND  ");
            mystats.rtype++;
            mystats.logical++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] & GPReg[inst1.Rt]); 
            break;

        case 9:
            printf(" ANDI ");
            mystats.itype++;
            mystats.logical++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] & inst1.Imm); 
            break;

        case 10:
            printf(" XOR  ");
            mystats.rtype++;
            mystats.logical++;
            GPReg[inst1.Rd] = (GPReg[inst1.Rs] ^ GPReg[inst1.Rt]); 
            break;

        case 11:
            printf(" XORI ");
            mystats.itype++;
            mystats.logical++;
            GPReg[inst1.Rt] = (GPReg[inst1.Rs] ^ inst1.Imm); 
            break;
    
        case 12:
            printf(" LDW  ");
            mystats.itype++;
            mystats.memAccess++;
            break;
    
        case 13:
            printf(" STW  ");
            mystats.itype++;
            mystats.memAccess++;
            break;
    
        case 14:
            printf(" BZ   ");
            mystats.itype++;
            mystats.ctrlTransfer++;
            break;
    
        case 15:
            printf(" BEQ  ");
            mystats.itype++;
            mystats.ctrlTransfer++;
            break;
    
        case 16:
            printf(" JR   ");
            mystats.itype++;
            mystats.ctrlTransfer++;
            break;
    
        case 17:
            printf(" HALT ");
            mystats.itype++;
            // I am not 100% confident that HALT counts as control transfer instruction...
            mystats.ctrlTransfer++;
            break;
    } //end of switch statement
} //end of function

void shift(int opcode, int Rs, int Rt, int Rd, int Imm) {
    
    // using assignment to copy entire struct for now... could use memcopy
    // or could also implement with arrays and a true shift register
    inst5 = inst4;
    inst4 = inst3;
    inst3 = inst2;
    inst2 = inst1;
    inst1.opcode = opcode;
    inst1.Rs = Rs;
    inst1.Rt = Rt;
    inst1.Rd = Rd;
    inst1.Imm = Imm;

    // update stats
    mystats.totalInst++;
    mystats.pc = (mystats.pc + 4);

} //end of shift register function 

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
