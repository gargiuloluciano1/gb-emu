//TODO fix naming
#include "register.h"

#include "emulator.h"
#include "sm64_io.h"

//TODO look on table for which register actually are called by some
//of this functions

//TODO add some flags to specify mode of function in handler functions
//TODO each isa has a fetch function but a lot share the same
//TODO maybe same type function

//(NOTE) add here because local to translation unit

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

#define sm83ld##rd##m(rd, m) \
int sm83ld##rd##m(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SET_FLAGS(0); \
    		i->rd = OperandSet(rd, 0, direct); \
    		i->m  = OperandSet(m,  0, direct); \
		return 0;\
}

#define sm83ldrd(rd) \
#define sm83ld##rd##m(rd,A) \
#define sm83ld##rd##m(rd,B) \
#define sm83ld##rd##m(rd,C) \
#define sm83ld##rd##m(rd,D) \
#define sm83ld##rd##m(rd,E) \
#define sm83ld##rd##m(rd,F) \
#define sm83ld##rd##m(rd,A) \
int sm83ld##rdhl(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SET_FLAGS(0); \
    		i->rd = OperandSet(rd, 0, direct); \
    		i->m  = OperandSet(HL,  0, indirect); \
		return 0;\
}

#define SM83LD_ALL()
#define sm83ld(A) \
#define sm83ld(B) \
#define sm83ld(C) \
#define sm83ld(D) \
#define sm83ld(E) \
#define sm83ld(F) \
#define sm83ld(A)

#define sm83ld##rdn(rd) \
int sm83ld##rdn(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(2, IO); \
    		i->rd = OperandSet(rd, 0, direct); \
    		i->m  = OperandSet(ReadNextByteFromMemory(),  1, direct); \
		return 0;\
}

#define SM83LDN_ALL() \
sm83ld##rdn(A)\
sm83ld##rdn(B)\
sm83ld##rdn(C)\
sm83ld##rdn(D)\
sm83ld##rdn(E)\
sm83ld##rdn(F)\
sm83ld##rdn(A)\

SM83LDN_ALL()

#define sm83hlm(m)\
int sm83ldhl##m(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, IO); \
    		i->rd = OperandSet(HL, 0, indirect); \
    		i->m  = OperandSet(m,  1, direct); \
		return 0;\
}

#define SM83LDHLM_ALL() \
sm83ldhl##m(A)\
sm83ldhl##m(B)\
sm83ldhl##m(C)\
sm83ldhl##m(D)\
sm83ldhl##m(E)\
sm83ldhl##m(F)\
sm83ldhl##m(A)

//LD (HL), n
int sm83lhln (State *s){
		pInstruction i = NextInstruction();

		INSTRUCTION_SET_INFO(2, IO);
		INSTRUCTION_SET_FLAGS(0);
		
		i->rd = OperandSet(HL ,0, indirect);
		i->m  = OperandSet(ReadNextByteFromMemory(), 1, direct);

		return 0;
}


//TODO chech this more accurately
#define HL
#define BC 
#define DE 

//LD A, (BC)
//r with 16 bit register
#define sm83ld(r, rr) \
int sm83labc (State *s){ \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		i->rd =OperandSet(r, 0, direct); \
		i->m = OperandSet(rr,0, indirect); \
		return 0; \
} \

//TODO need to add all of these
#define sm83ldr(r) \
#define sm83ld(r, BC) \
#define sm83ld(r, DE) \
#define sm83ld(r, CA) \

#define SM83LD_16_ALL() \
sm83ldr(A) \
sm83ldr(B) \
sm83ldr(C) \
sm83ldr(D) \
sm83ldr(E) \
sm83ldr(F) \

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

//NOTE where n is immediate, find better naming
//for the moment leave like this
#define sm83ldrn(rd) \
int sm83ldrn (State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(2, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd = OperandSet(rd, 0, index | indirect); \
		i->m  = OperandSet(LoadNextByteFromMemory(), 1, index | indirect); \
		return 0; \
}


#define sm83ldnm(m) \
int sm83ldn##m (State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(2, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd = OperandSet(ReadNextByteFromMemory(), 1, \
					indexed | indirect); \
		i->m  = OperandSet(m, 0, direct); \
		return 0; \
}

#define sm83ldrdnn(rd) \
int sm83ld##rdnn(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(3, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(rd, 0, direct); \
		i->m   = OperandSet(ReadNextHWordFromMemory(), 1, indirect)\
		return 0; \
}

//TODO little endian?
//LD A, (nn)

#define sm83ldnnm(m) \
int sm83ldnn##m(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(3, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(ReadNextHWordFromMemory(), 1, indirect)\
		i->m   = OperandSet(m, 0, direct); \
		return 0; \
}

#define sm83ldrdhli(rd) { \
int sm83ldrd##hli(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(3, IO); \
		INSTRUCTION_SETFLAGS(INC); \
		i->rd  = OperandSet(rd, 0, direct)\
		i->m   = OperandSet(HL, 0, indirect); \
		return 0; \
}\

#define sm83ldhlird(m) { \
int sm83ldhli##m(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(INC); \
		i->rd  = OperandSet(rd, 0, indirect)\
		i->m   = OperandSet(m, 0, direct); \
		return 0; \
}\

#define sm83ldrdhld(rd) { \
int sm83ldrd##hld(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(DEC); \
		i->rd  = OperandSet(rd, 0, direct)\
		i->m   = OperandSet(HL, 0, indirect); \
		return 0; \
}\

#define sm83ldhldm(m) { \
int sm83ldhld##m(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(DEC); \
		i->rd  = OperandSet(HL, 0, indirect)\
		i->m   = OperandSet(m, 0, direct); \
		return 0; \
}\

//ld a16r 
#define sm83rrm(rr, m) \
int sm83ld##rr##m(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(rr, 0, indirect)\
		i->m   = OperandSet(m, 0, direct); \
		return 0; \
}\

#define sm83rr(rr) \
sm83rrm(rr, m) \
sm83rrm(rr, m) \
sm83rrm(rr, m) \
sm83rrm(rr, m) \
sm83rrm(rr, m) \
sm83rrm(rr, m) \
sm83rrm(rr, m)

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


#define sm83ldrrnn(rr) \
int sm83ld##rr(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(3, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(rr, 0, direct)\
		i->m   = OperandSet(ReadNextHWordFromMemory(), 1, direct); \
		return 0; \
}\


//TODO rewrite in case other rr registe might be used,
//not specified not sure

//LD SP, HL
int sm83lsphl (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(1, IO_16);
		INSTRUCTION_SETFLAGS(0);

		i->rd = OperandSet(SP_16, 0, direct);
		i->m =  OperandSet(HL_16, 0, direct);

		return 0;
}

#define sm83ldpush(qq) \
int sm83ldpush##qq(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(qq, 0, direct)\
		return 0; \
}\

#define SM83LDPUSH_ALL()\
sm83ldpush(qq) \
sm83ldpush(qq) \
sm83ldpush(qq) \
sm83ldpush(qq)

#define sm83ldpop(qq) \
int sm83ldpop##qq(State *s) { \
		pInstruction i = NextInstruction(); \
		INSTRUCTION_SET_INFO(1, IO); \
		INSTRUCTION_SETFLAGS(0); \
		i->rd  = OperandSet(qq, 0, direct)\
		return 0; \
}\

#define SM83LDPOP_ALL() \
sm83ldpop(qq) \
sm83ldpop(qq) \
sm83ldpop(qq) \
sm83ldpop(qq)

#define SM83_OP_ALL() \
#define SM83LDPUSH_ALL()\
#define SM83LDPOP_ALL() \

SM83_OP_ALL()
   
int sm83ldhlspe (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(2, IO_16);
		INSTRUCTION_SETFLAGS(LDHL); //TODO flag because signed

		i->rd = OperandSet(HL_16, 0, direct);
		i->m =  OperandSet(ReadNextByteFromMemory(), 1, direct);

		return 0;
}

//LDHL SP, e
int sm83ldhlspe (State *s) {
		pInstruction i = NextInstruction();

		ADD_INSTRUCTION_INFO(2, IO_16);
		INSTRUCTION_SETFLAGS(LDHL);

		i->rd = OperandSet(HL_16, 0, direct);
		i->m =  OperandSet(ReadNextByteFromMemory(), 1, direct);

		return 0;
}
//LD (nn), SP
//(NOTE) isnt this just two load instructions to nn and nn+1?
int sm83ldnnsp (State *s) {
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
