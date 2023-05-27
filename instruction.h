
typedef unsigned int INST_TYPE;

struct instruction {
	int opcode;
	char opcode_namep[5];
	
	int rs;
	int rt;
	int rd;

	INST_TYPE TYPE;
	int ready;
};

void print_inst(struct instruction);
struct instruction fill_instruction(int bin_inst[], int len);

