
struct instruction {
	int opcode;
	char opcode_name[5];
	
	int rs;
	int rt;
	int rd;
	int imm;

	int TYPE;
	int ready;
};

void print_inst(struct instruction);
struct instruction fill_instruction(int bin_inst[], int len);

