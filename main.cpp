#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "emulator.h"

//TODO make a header only for definitions
#if 0
sm83_instruction ldrhl() {
		BYTE op = OP;
		BYTE len = 1;
		BYTE type = sm83_instruction-type.LD8b;

		BYTE flags = 0;
		BYTE flags = ld8b-flags.DEREF2; //needs to be read as a pointer
}
#endif

//TODO put everything in a global namespace
//======First Stage Interpretation======


typedef sm83_instruction Instruction;
int main(int argc, char** argv) {
		if (argc < 1) {
				fprintf(stderr, "Not enough args\n");
				return 1;
		}
		//TODO needs further error checking
		int fd = open(argv[1], O_RDONLY);

		while(read(fd, op, sizeof(op)) > 0) {
				if (is_prefix(op)) { //call other routine
				}

				table[op].routine(); //in fetching alway increase CODE[] table
									   //always know where next one is

				s->spc+=i->len; //(NOTE) might not be always correct
				++s->tcp;
		}
		return 0;
}
