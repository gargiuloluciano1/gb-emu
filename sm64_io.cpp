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

//LD R, R'
int sm83ldrr(State *s) {
		//BYTE opcode = s->cpu->ir;  //fist instruction
		pInstruction *i = NextInstruction();

		//op len type
		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SET_FLAGS(0);

		i->rd = OperandSet(Getr(i->op),  0, direct);
		i->m  = OperandSet(Getrr(i->op), 0, direct);

		return 0;
}

//LD r, n
int sm83ldrn(State *s) {
		pInstruction *i = NextInstruction();

		//TODO should immediate instruction be 2 bytes long?
		INSTRUCTION_SET_INFO(2, IO);
		INSTRUCTION_SET_FLAGS(0);

		//i would need to fetch again here
		i->rd = OperandSet(Getr(i->op),  0, direct);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1, immediate);

		return 0;
}

//LD r, (HL)
int sm83ldrhl(State *s) {
		pInstruction *i = NextInstruction();

		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SET_FLAGS(0);

		i->rd  = OperandSet(Getr(i->op), 0, direct);
		i->m   = OperandSet(HL, 0, indirect);

		return 0;
}

//LD (hl), r
int sm83lhlr(State *s) {
		pInstruction i = NextInstruction();
		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SET_FLAGS(0);

		i->rd = OperandSet(HL, 0, indirect);
		i->m  = OperandSet(Getrr(i->op), 0, direct);

		return 0;
}

//LD (HL), n
int sm83lhln (State *s){
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(2, IO);
		INSTRUCTION_SET_FLAGS(0);
		
		i->rd = OperandSet(HL ,0, indirect);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1, direct);

		return 0;
}

//LD A, (BC)
int sm83labc (State *s){
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SET_FLAGS(0);

		i->rd =OperandSet(A, 0, direct);
		i->m = OperandSet(BC,0, indirect);

		return 0;
}

//LD A, (DE)
int sm83lade (State *s){
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SET_FLAGS(0);

		i->rd =OperandSet(A, 0, direct);
		i->m = OperandSet(DE,0, indirect);

		return 0;
}

//index mode
//LD A, C
int sm83lac (State *s){
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(A, 0, direct); 
		i->m  = OperandSet(C, 0, index);

		return 0;
}

//needs to be done first sum C + FF00 then indirection
//LD (C), A
int sm83lca (State *s) {
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(1, IO);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(C, 0, index | indirect);
		i->m  = OperandSet(A, 0, direct);

		return 0;
}

//LD A, (n)
int sm83lan (State *s) {
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(2, IO);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(A, direct);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1,
				    indexed | indirect);

		return 0;
}

//LD (n), A
int sm83lnina (State *s) {
		pInstruction i = NextpInstruction();

		ADD_INSTRUCTION_INFO(2, IO);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(ReadNextByteFromMemory(), 1,
					indexed | indirect);
		i->m  = OperandSet(A, 0, direct);

		return 0;
}

//TODO little endian?
//LD A, (nn)
int sm83lann (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(3, InstructionType.load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(A,0,index);
		i->m  = OperandSet(ReadNextHWordFromMemory(), 1, indirect);

		return 0;
}

//LD (nn), A
int sm83lnna (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(3, InstructionType.load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, indirect);
		i->m  = OperandSet(A, 0,direct);

		return 0;
}

// LD A, (HLI)
int sm83lahli(State *s) {
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

// =======16b io instructions==============

//   dd     r
// BC	   00
// DD      01
// HL	   10
// SP      11

#define BC_16 0
#define DD_16 1
#define HL_16 2
#define SP_16 3


// Low address first
//LD dd, nn
int sm83lddnn (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(3, IO_16);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(Getdd(i->op),  0, direct);
		i->m =  OperandSet(ReadNextHWordFromMemory(), 1, direct);

		return 0;
}

//TODO important stack operation
//LD SP, HL
int sm83lsphl (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, IO_16);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(SP_16, 0, direct);
		i->m =  OperandSet(HL_16, 0, direct);

		return 0;
}

int sm83pushqq (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, IO_16);
		INSTRUCTION_SETFLAGS(PUSH);

		i->rd = OperandSet(Getdd(i->op), 0, direct);

		return 0;
}

int sm83popqq (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, IO_16);
		INSTRUCTION_SETFLAGS(POP);

		i->rd = OperandSet(Getdd(i->op), 0, direct);

		return 0;
}

//LDHL SP, e
int sm83lhlspe (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(2, IO_16);
		INSTRUCTION_SETFLAGS(LDHL);

		i->rd = OperandSet(HL_16, 0, direct);
		i->m =  OperandSet(ReadNextByteFromMemory(), 1, direct);

		return 0;
}
//LD (nn), SP
//(NOTE) isnt this just two load instructions to nn and nn+1?
int sm83lnnsp (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(3, IO_16);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, indirect);
		i->m =  OperandSet(SP_16, 0, direct);

		return 0;
}

int sm83lddnn (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, load);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(rDE, 0, indirect);
		i->m =  OperandSet(A, 0, indirect);

		return 0;
}
