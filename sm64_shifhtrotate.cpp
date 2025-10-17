#include "emulator.h"

int sm64rlca(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RLCA); 
		return 0;
}

int sm64rla(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RLA); 
		return 0;
}


int sm64rrca(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RRCA); 
		return 0;
}

int sm64rra(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RRA); 
		return 0;
}

int sm64rlc(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RLC); 
		return 0;
}

#define sm64rlcm(m) \
int sm64rlc##m(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(1, SRT);  \
		INSTRUCTION_SET_FLAGS(RLC);  \
    		i->rd = OperandSet(m, 0, direct); \
		return 0; \
}

//TODO 
//
// THIS ARE  2 BYTES OPERATION
// THEY HAVE PREFIX BEFORE
//

#define sm64rlc \
sm64rlcm(A) \
sm64rlcm(B) \
sm64rlcm(C) \
sm64rlcm(D) \
sm64rlcm(E) \
sm64rlcm(L) \
sm64rlcm(H) \
int sm64rlchl(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(1, SRT);  \
		INSTRUCTION_SET_FLAGS(RLC);  \
    		i->rd = OperandSet(HL, 0, indirect); \
		return 0; \
}\
