#include "emulator.h"
#include "sm64_io.h"
//(NOTE) add here because local to translation unit
#define A 0x7
#define B 0x0
#define C 0x1
#define D 0x5
#define E 0x3
#define H 0x4
#define L 0x5

//========LD 8b INSTRUCTIONS==========
//TODO decide a naming conventions

// Register		rr'
//
//    A
//    B
//    C
//    D
//    E
//    H
//    L

//TODO
//(Note) should put all this in main header?
//Aliases
typedef sm83_instruction Instr;
typedef sm83_cpu Cpu;

//=======Inline Functions==========

/* 
 * (Note)
 *
 * Not yet decided on how to implement these
 * Should make function call every time the 
 * State involved? because structure could
 * change NOT want to rewrite all instructions
 *
 * Maybe should imitate interactions bw cpu
 * and rest of board
 * Add set of functions to interact bw cpu and state
 */

//TODO add to other general header
//this would be the api
//(NOTE) bad because never any error checks

#define INCCOUNTER() \
s->cpu->pc = s->cpu->pc + i->len; \
++s->tcp

#define ADD_INSTRUCTION_INFO(len, type) \
		i->op	 = s->cpu->ir;\
		i->len   = (len);\
		i->type  = (type)

#define READ_IMMEDIATE_8b() \
		s->memory[s->pc + 1];

int sm83ldrr(State *s) {
		//BYTE opcode = s->cpu->ir;  //fist instruction
		Instr *i = s->code[s->tpc];

		ADD_INSTRUCTION_INFO(1, 0);
		i->flags = 0;

		i->op1 = (OP&0x38) >>3; //takes two register ids
		i->op2 = OP&0x07;

		INCCOUNTER();
		return 0;
}

int sm83ldrn(State *s) {
		Instr *i = s->code[s->tpc];
		ADD_INSTRUCTION_INFO(1, 0)

		BYTE flags = 0;
		//TODO change naming
		i->flags += ld8b-flags.IMM;

		//i would need to fetch again here
		i->op1 = (OP&0x38) >>3; //takes two register ids
		i->op2 = READ_IMMEDIATE_8b();
		ASSERT(1); //TODO testing needed, is stored high[7 0] or low[2 0]

		return 0;
}

