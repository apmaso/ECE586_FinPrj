
typedef unsigned int INST_TYPE;

struct instruction2 {
	int opcode;
	char opcode_namep[4];
	
	int rs;
	int rt;
	int rd;

	INST_TYPE TYPE;
	int ready;
};

void print_inst(struct instruction2);
struct instruction2 fill_instruction2(int bin_inst[], int len);

