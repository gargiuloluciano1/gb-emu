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

#define HL
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
typedef sm83_instruction Instruction;
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


int sm83ldrr(State *s) {
		//BYTE opcode = s->cpu->ir;  //fist instruction
		Instruction *i = NextInstruction();
		ADD_INSTRUCTION_INFO(1, 0);
		INSTRUCTION_SETFLAGS(0);

		i->op1 = GETr(i->op);
		i->op2 = GETrr(i->op);

		return 0;
}

int sm83ldrn(State *s) {
		Instruction *i = NextInstruction();

		//TODO should immediate instruction be 2 bytes long?
		ADD_INSTRUCTION_INFO(2, 0)
		INSTRUCTION_SETFLAGS(0);

		//i would need to fetch again here
		i->op1 = (OP&0x38) >>3; //takes two register ids
		i->op2 = ReadByteFromMemory(addr);

		ASSERT(1); //TODO testing needed, is stored high[7 0] or low[2 0]
		return 0;
}

int sm83ldrhl(State *s) {
		Instruction *i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, 0);
		INSTRUCTION_SETFLAGS(0);

		i->op1 = (i->op&0x38) >>3; //takes two register ids
		i->op2 = HL;

		ASSERT(1);
		return 0;
}
int sm83lhlr(State *s) {
		Instruction i = NextInstruction();
		ADD_INSTRUCTION_INFO(1, 0);
		INSTRUCTION_SETFLAGS(0);

		ASSERT(1);
		return 0;
}

