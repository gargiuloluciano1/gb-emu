#include "emulator.h"
#include "sm64_io.h"

//
//
//(NOTE) add here because local to translation unit
#define A 0x7
#define B 0x0
#define C 0x1
#define D 0x5
#define E 0x3
#define H 0x4
#define L 0x5

//16 bit register codes
#define HL 0x6 //110

// as m
#define BC 0xE //001 110
#define DE 0x1E //011 110

// as rd
#define BCr 0x2 // 000 010
#define DEr 0x22 //010 010
				
//========LD 8b INSTRUCTIONS==========

// Register		rr'
//
//    A
//    B
//    C
//    D
//    E
//    H
//    L

// Naming Conventions for now
// sm83{t}{rd}[am]{m}[inc/dec][am]
// t = l (load)
// am = access mode
// m  = r/ r or 16r or n
//

//Aliases
typedef sm83_instruction* pInstruction;
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

#define LOADINSTRUCTIONS_BEGIN() \
		ADD_INSTRUCTION_INFO(1, InstructionType.load)

int sm83ldrr(State *s) {
		//BYTE opcode = s->cpu->ir;  //fist instruction
		pInstruction *i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->op1 = GETr(i->op);
		i->op2 = GETrr(i->op);

		return 0;
}

int sm83ldrn(State *s) {
		pInstruction *i = NextInstruction();

		//TODO should immediate instruction be 2 bytes long?
		LOADINSTRUCTIONS_DEFAULT();

		//i would need to fetch again here
		i->op1 = (OP&0x38) >>3; //takes two register ids
		i->op2 = ReadByteFromMemory(addr);

		ASSERT(1); //TODO testing needed, is stored high[7 0] or low[2 0]
		return 0;
}

int sm83ldrhl(State *s) {
		pInstruction *i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->op1 = (i->op&0x38) >>3; //takes two register ids
		i->op2 = HL;

		ASSERT(1);
		return 0;
}

int sm83lhlr(State *s) {
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->op1=0x6;
		i->op2=(i->op&0x38) >>3;

		ASSERT(1);
		return 0;
}

int sm83lhln (State *s){
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();
		
		i->rd = OperandSet(HL,0, indirect);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1, .direct);

		ASSERT(1);
		return 0;
}

int sm83labc (State *s){
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();
		

		i->rd =OperandSet(A,  .direct);
		i->m = OperandSet(BC, .indirect);

		ASSERT(1);
		return 0;
}

int sm83lade (State *s){
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->rd =OperandSet(A,  .direct);
		i->m = OperandSet(DE, .indirect);

		ASSERT(1);
		return 0;
}

//index mode
int sm83lac (State *s){
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->rd = OperandSet(A, .direct); 
		i->m  = OperandSet(C, .index);

		ASSERT(1);
		return 0;
}
//needs to be done first sum C + FF00 then indirection
int sm83lca (State *s) {
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->rd = OperandSet(C, index | indirect);
		i->m  = OperandSet(A, direct);

		ASSERT(1);
		return 0;
}

int sm83lanin (State *s) {
		pInstruction i = NextInstruction();

		LOADINSTRUCTIONS_DEFAULT();

		i->rd = OperandSet(A, direct);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1,
					      indexed | indirect);

		return 0;
}

int sm83lnina (State *s) {
		pInstruction i = NextpInstruction();

		ADD_INSTRUCTION_INFO(2, InstructionType.load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(ReadNextByteFromMemory(), 1,
							indexed|indirect);
		i->m  = OperandSet(A, direct);

		return 0;
}

int sm83lann (State *s) {
		pInstruction i = NextInstruction();
		ADD_INSTRUCTION_INFO(3, InstructionType.load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(A,0,index);
		i->m  = OperandSet(ReadNextHWordFromMemory(), 1, indirect);

		return 0;
}

int sm83lnnia (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(3, InstructionType.load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, indirect);
		i->m  = OperandSet(A, 0,direct);

		return 0;
}

// LD A, (HLI)
int sm83lahlinci(State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, InstructionType.load);
		INSTRUCTION_SETFLAGS(INC_M);

		i->rd = OperandSet(A,  0, direct);
		i->m  = OperandSet(HL, 0, indirect);

		return 0;
}

// LD (HLI), A
int sm83lhlia(State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, InstructionType.load);
		INSTRUCTION_SETFLAGS(INC_RD);

		i->rd= OperandSet(HL, 0, indirect);
		i->m = OperandSet(A,  0, direct);

		return 0;
}
// LD a, (HLD)
int sm83lahld(State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, InstructionType.load);
		INSTRUCTION_SETFLAGS(DEC_M);

		i->rd= OperandSet(A,0, direct);
		i->m = OperandSet(HL, 0, indirect);

		return 0;
}

// LD (HLD), A
int sm83lhlda (State *s){
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, InstructionType.load);
		INSTRUCTION_SETFLAGS(DEC_RD);

		i->rd= OperandSet(HL, 0, indirect);
		i->m = OperandSet(A, 0,  direct);

		return 0;
}

int sm83lbca (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(rBC, 0, indirect);
		i->m =  OperandSet(A, 0, indirect);

		return 0;
}

int sm83ldea (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(rDE, 0, indirect);
		i->m =  OperandSet(A, 0, indirect);

		return 0;
}
