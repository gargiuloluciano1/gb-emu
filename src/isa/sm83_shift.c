include "emulator.h"

int sm83rlca(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RLCA); 
		return 0;
}

int sm83rla(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RLA); 
		return 0;
}


int sm83rrca(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RRCA); 
		return 0;
}

int sm83rra(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
		INSTRUCTION_SET_FLAGS(RRA); 
		return 0;
}


int sm83rlc(State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(1, SRT); 
			INSTRUCTION_SET_FLAGS(RLC); 
		return 0;
}


//TODO these are preceded by prefix 0xCD
//Assume called from other table, so only look at second part
//Are len 2

#define SM83_DEFINE_OP_M(op, m) \
int sm83##op##m(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(op);  \
    		i->rd = OperandSet(m, 0, direct); \
			return 0; \
} \

#define SM83_DEFINE_OP(op) \
SM83_DEFINE_OP_M(op, a) \
SM83_DEFINE_OP_M(op, b) \
SM83_DEFINE_OP_M(op, c) \
SM83_DEFINE_OP_M(op, d) \
SM83_DEFINE_OP_M(op, e) \
SM83_DEFINE_OP_M(op, f) \
SM83_DEFINE_OP_M(op, l) \
int sm83##ophl(State *s) { \
    		pInstruction i = NextInstruction();  \
    		INSTRUCTION_SET_INFO(2, SRT);  \
			INSTRUCTION_SET_FLAGS(op);  \
    		i->rd = OperandSet(HL, 0, indirect); \
			return 0; \
} \

#define SM83_DEFINE_ALL() \
SM83_DEFINE_OP(rlc) \
SM83_DEFINE_OP(rl) \
SM83_DEFINE_OP(rrc) \
SM83_DEFINE_OP(rr) \
SM83_DEFINE_OP(sla) \
SM83_DEFINE_OP(sra) \
SM83_DEFINE_OP(srl) \
SM83_DEFINE_OP(swap)

SM83_DEFINE_ALL()
