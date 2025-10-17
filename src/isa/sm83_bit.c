#include "emulator.h"

#define SM83_BIT_B_M(b, m) \
int sm83_bit_#b#m(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(BIT);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(m, 0, direct); \
			return 0; \
}

#define SM83_BIT_B(b) \
#define SM83_BIT_B_M(b, a) \
#define SM83_BIT_B_M(b, b) \
#define SM83_BIT_B_M(b, c) \
#define SM83_BIT_B_M(b, d) \
#define SM83_BIT_B_M(b, e) \
#define SM83_BIT_B_M(b, f) \
#define SM83_BIT_B_M(b, l) \
int sm83_##bhl() { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(BIT);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(hl,0,indirect); \
			return 0; \
}\ 

#define SM83_BIT_ALL() \
#define SM83_BIT_B(0) \
#define SM83_BIT_B(1) \
#define SM83_BIT_B(2) \
#define SM83_BIT_B(3) \
#define SM83_BIT_B(4) \
#define SM83_BIT_B(5) \
#define SM83_BIT_B(6) \
#define SM83_BIT_B(7) \


#define SM83_SET_B_M(b, m) \
int sm83_res#b#m(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(BIT);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(m, 0, direct); \
			return 0; \
}

#define SM83_SET_B(b) \
#define SM83_SET_B_M(b, a) \
#define SM83_SET_B_M(b, b) \
#define SM83_SET_B_M(b, c) \
#define SM83_SET_B_M(b, d) \
#define SM83_SET_B_M(b, e) \
#define SM83_SET_B_M(b, f) \
#define SM83_SET_B_M(b, l) \
int sm83_set_##bhl() { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(SET);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(hl,0,indirect); \
			return 0; \
}\ 

#define SM83_SET_ALL() \
#define SM83_SET_B(0) \
#define SM83_SET_B(1) \
#define SM83_SET_B(2) \
#define SM83_SET_B(3) \
#define SM83_SET_B(4) \
#define SM83_SET_B(5) \
#define SM83_SET_B(6)
#define SM83_SET_B(7)


#define SM83_RES_B_M(b, m) \
int sm83_res#b#m(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(BIT);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(m, 0, direct); \
			return 0; \
}

#define SM83_RES_B(b) \
#define SM83_RES_B_M(b, a) \
#define SM83_RES_B_M(b, b) \
#define SM83_RES_B_M(b, c) \
#define SM83_RES_B_M(b, d) \
#define SM83_RES_B_M(b, e) \
#define SM83_RES_B_M(b, f) \
#define SM83_RES_B_M(b, l) \
int sm83_res##bhl() { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(SET);  \
    		i->rd = OperandSet(b, 0, direct); \
			i->m  = OperandSet(hl,0,indirect); \
			return 0; \
}\ 

#define SM83_RES_ALL() \
#define SM83_RES_B(0) \
#define SM83_RES_B(1) \
#define SM83_RES_B(2) \
#define SM83_RES_B(3) \
#define SM83_RES_B(4) \
#define SM83_RES_B(5) \
#define SM83_RES_B(6) \
#define SM83_RES_B(7)

#define SM83_BIT_DEFINE_ALL() \
SM83_BIT_ALL() \
SM83_SET_ALL() \
SM83_RES_ALL()

SM83_BIT_DEFINE_ALL()
