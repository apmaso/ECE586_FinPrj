#include <stdio.h>
#include <math.h>
#include <stdint.h>

int * dec2binOp(int decimal);
int * dec2binRt(int decimal);
int * dec2binRs(int decimal);
int * dec2binRd(int decimal);
int * dec2binImm(int decimal);
uint32_t ConvertToDec(uint32_t* bits, uint32_t size);

int main() {

    // 0 = R-Type and 1 = I-Type
    int type;
    int opcode_dec;
    int rd_dec;
    int rs_dec;
    int rt_dec;
    int imm_dec;
//    char filename[20];
    int new_inst_flag = 1;
    int input_flag;
    int copies = 0;
    // int arrays to hold binary values
    int binary_inst[32]; 
    int reverse[32]; 
    int *opcode_bin;
    int *rd_bin;
    int *rs_bin;
    int *rt_bin;
    int *imm_bin;
    
    char hex[9];
    uint32_t result;
    uint32_t len;
    uint32_t binConv[32];
    // Prompt for filename
/*    printf("What would you like to name the image file?");
    scanf("char *", &filename);
    FIXME: Taking user input for filename was way more trouble than its worth, hardcoding it for now
*/
    // Open the file
	FILE *fp;
    fp = fopen("test.txt", "w");
    
    while(new_inst_flag) {
        
        // While we are still writing instructions, open file for writing
	    FILE *fp;
        fp = fopen("test.txt", "w");
        
        printf("R or I type? (0 for R-Type, 1 for I-Type)");
        scanf("%d", &type);
        printf("Opcode?");
        scanf("%d", &opcode_dec);
        printf("Rt?");
        scanf("%d", &rt_dec);
        printf("Rs?");
        scanf("%d", &rs_dec);
        
        if(type){ 
            printf("Imm?");
            scanf("%d", &imm_dec);
        }
        else{
            printf("Rd?");
            scanf("%d", &rd_dec); 
        }

        // Change the decimal values to binary ones
        opcode_bin = dec2binOp(opcode_dec);
        rt_bin = dec2binRt(rt_dec);
        rs_bin = dec2binRs(rs_dec);
        rd_bin = dec2binRd(rd_dec);
        imm_bin = dec2binImm(imm_dec);
       
        // Debugging info
        printf("Decimal Values");
        printf("Opcode = %d \n", opcode_dec);
        printf("Rt = %d \n", rt_dec);
        printf("Rs = %d \n", rs_dec);
        if (type) {
            printf("Imm = %d \n", imm_dec); 
        }
        else {
            printf("Rd = %d \n", rd_dec);
        }

        
        // print out binary values to check function
        printf("Opcode=  ");
        for (int k=5; k>=0; k--){     
            printf("%d ", opcode_bin[k]); 
        }
        printf("\n");
        printf("Rt=  ");
        for (int l=4; l>=0; l--){     
            printf("%d ", rt_bin[l]); 
        }
        printf("\n");
        printf("Rs=  ");
        for (int m=4; m>=0; m--){     
            printf("%d ", rs_bin[m]); 
        }
        printf("\n");
        if (type) {
            printf("Imm=  ");
            for (int p=15; p>=0; p--){     
                printf("%d ", imm_bin[p]); 
            }
        }
        else {
            printf("Rd=  ");
            for (int n=4; n>=0; n--){     
                printf("%d ", rd_bin[n]); 
            }
        }    
        printf("\n");


        // load the various binary values into a single array
        for (int a=31; a>25; a--) {
            binary_inst[a] = opcode_bin[(a-26)];
        }
        for (int a=25; a>20; a--) {
            binary_inst[a] = rs_bin[(a-21)];
        }
        for (int a=20; a>15; a--) {
            binary_inst[a] = rt_bin[(a-16)];
        }
        if(type) { 
            for (int a=15; a>=0; a--) {
                binary_inst[a] = imm_bin[(a)];
            }
        }
        else{
            // R-Type Instruction
            for (int a=15; a>10; a--) {
                binary_inst[a] = rd_bin[(a)];
            }
            for (int a=10; a>=0; a--) {
                binary_inst[a] = 0; 
            }
        }

        // Print out entire array for debugging purposes
        printf("All together now\n");
        for (int c=31; c>=0; c--) {
            printf("%d ", binary_inst[c]);
        }
        printf("\n");

        // flip binary word around so MSB=0 <---> LSB=31 
        for (int e=0; e<32; e++) {
            reverse[31-e] = binary_inst[e]; 
        }       

        // change to array of uint32 
        for (int d=31; d>=0; d--) {
             binConv[d] = reverse[d];
        }
       
        len = (sizeof(binConv) / sizeof(binConv[0])); // get array size
        result = ConvertToDec(binConv, len);
        sprintf(hex, "%08x", result);
        printf("32 bit Hex Instruction:%s\n", hex);
        
        
        // Prompt user for the desired number copies of the current instruction
        printf("How many copies of this instruction?");
        scanf("%d", &copies);

        while(copies > 0) {
            fprintf(fp, "%s\n", hex);
            copies--;
        }
    
        // Prompt user and ask if there are more instruction 
        printf("Would you like to add more instructions? (1 for yes, 0 for no)");
        scanf("%d", &input_flag);
        new_inst_flag = input_flag;    
    }
    fclose(fp);

    return 0; 
} // end of main

int * dec2binRs(int decimal) {
    // int array to hold binary value 
    static int rs_binary[5];

    for (int i=4; i>=0; i--) {
        if (pow(2, i) <= decimal) {
            rs_binary[i] = 1;
            decimal = decimal - pow(2, i); 
        }
        else {
            rs_binary[i] = 0;
        }
    }
    //return binary value;  
    return rs_binary;  
}//end of dec2binRs

int * dec2binImm(int decimal) {
    // int array to hold binary value 
    static int imm_binary[16];

    if (decimal < 0) {
        decimal = decimal * -1;
        imm_binary[15] = 1;
        for (int i=14; i>=0; i--) {
            if (pow(2, i) <= decimal) {
                imm_binary[i] = 1;
                decimal = decimal - pow(2, i); 
            }
            else {
                imm_binary[i] = 0;
            }

        }
    }
    else {
        imm_binary[15] = 0;
        for (int i=14; i>=0; i--) {
            if (pow(2, i) <= decimal) {
                imm_binary[i] = 1;
                decimal = decimal - pow(2, i); 
            }
            else {
                imm_binary[i] = 0;
            }
        }
    }    
    //return binary value;  
    return imm_binary;  
}//end of dec2binImm

int * dec2binRt(int decimal) {
    // int array to hold binary value 
    static int rt_binary[5];

    for (int i=4; i>=0; i--) {
        if (pow(2, i) <= decimal) {
            rt_binary[i] = 1;
            decimal = decimal - pow(2, i); 
        }
        else {
            rt_binary[i] = 0;
        }
    }
    //return binary value;  
    return rt_binary;  
}//end of dec2binRt


int * dec2binRd(int decimal) {
    // int array to hold binary value 
    static int rd_binary[5];

    for (int i=4; i>=0; i--) {
        if (pow(2, i) <= decimal) {
            rd_binary[i] = 1;
            decimal = decimal - pow(2, i); 
        }
        else {
            rd_binary[i] = 0;
        }
    }
    //return binary value;  
    return rd_binary;  
}//end of dec2binRd

int * dec2binOp(int decimal) {
    // int array to hold binary value 
    static int op_binary[6];

    for (int i=5; i>=0; i--) {
        if (pow(2, i) <= decimal) {
            op_binary[i] = 1;
            decimal = decimal - pow(2, i); 
        }
        else {
            op_binary[i] = 0;
        }
    }
    //return binary value;  
    return op_binary;  
}//end of dec2binOp

uint32_t ConvertToDec(uint32_t* bits, uint32_t size)
{
    uint32_t result = 0;

    for (uint32_t i = 0; i < size; i++) {

        result |= bits[i];
        if(i != size-1)
            result <<= 1;
    }

    return result;
}
