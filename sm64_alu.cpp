//TODO maybe instead just forward declare or think like extern variables
#include "emulator.h"

//TODO check this might not be correct
#define A  0x7
#define B  0x0
#define C  0x1
#define D  0x5
#define E  0x3
#define F  0x4
#define L  0x5
#define HL 0x6

typedef sm83_instruction* pInstruction;

#define sm83(op, r) \
int sm83##op##r(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, ALU); \
		INSTRUCTION_SET_FLAGS(op); \
    		i->rd = OperandSet(r, 0, direct); \
		return 0;\
}

#define x(op) \
int sm83##op##n(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(2, ALU); \
		INSTRUCTION_SET_FLAGS(op); \
    		i->rd = OperandSet(ReadNextByteFromMemory(), 0, direct); \
    return 0; \
}\
int sm83##op##hl(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, ALU); \
		INSTRUCTION_SET_FLAGS(op); \
    		i->rd = OperandSet(HL, 0, indirect);\
		return 0;\
}\
sm83(op,A) \
sm83(op,B) \
sm83(op,C) \
sm83(op,D) \
sm83(op,E) \
sm83(op,L) \


x(ADD)
x(SUB)
x(ADC)
x(SBC)
x(AND)
x(OR)
x(XOR)

//TODO maybe this is better way?
#define sm83inc(r)\
int sm83inc##r(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, ALU); \
		INSTRUCTION_SET_FLAGS(INC); \
    		i->rd = OperandSet(r, 0, direct);\
		return 0;\
}

sm83inc(A)
sm83inc(B)
sm83inc(C)
sm83inc(D)
sm83inc(E)
sm83inc(E)
sm83inc(L)

#define sm83dec(r)\
int sm83dec##r(State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(1, ALU); \
		INSTRUCTION_SET_FLAGS(DEC); \
    		i->rd = OperandSet(r, 0, direct);\
		return 0;\
}

sm83dec(A)
sm83dec(B)
sm83dec(C)
sm83dec(D)
sm83dec(E)
sm83dec(E)
sm83dec(L)
