#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "emulator.h"

//TODO make a header only for definitions



//TODO put everything in a global namespace

//======First Stage Interpretation======
//All routines are added in this table

State *s;
s->tpc   =0;
s->spc   =0;
s->icount=0;

sm83_instruction routine[] = 
{ 
};

typedef sm83_instruction Instruction;



int main(int argc, char** argv) {
		if (argc < 1) {
				fprintf(stderr, "Not enough args\n");
				return 1;
		}
		//TODO needs further error checking
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0) {
				fprint(stderr, "Fd was negative\n");
				return 1;
		}

		while(read(fd, op, sizeof(op)) > 0 ) {
				if (is_prefix(op)) { //call other routine
				}

				i->dispatch = routine[op];
				i->dispatch(s);

				//TODO probably better to read from a buffer rather than FILE pointer
				lseek(fd, i->len - 1, SEEK_CUR);
				++s->icount;
		}

		return 0;
}
