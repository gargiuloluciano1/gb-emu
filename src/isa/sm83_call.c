#include "emulator.h"

//little endian
int sm83callnn (State *s) {
    		pInstruction i = NextInstruction();
    		INSTRUCTION_SET_INFO(3, CALL);
			INSTRUCTION_SET_FLAGS(CALL);
    		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, direct);

			return 0;
}

#define SM83_CALL_CC(cc) \
int sm84call##ccnn (State *s) { \
    		pInstruction i = NextInstruction();\
    		INSTRUCTION_SET_INFO(3, CALL);\
			INSTRUCTION_SET_FLAGS(cc);\
    		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, direct);\
			return 0;\
}

#define SM83_CALL_CC_ALL() \
SM83_CALL_CC(NZ)\
SM83_CALL_CC(Z)\
SM83_CALL_CC(NC)\
SM83_CALL_CC(C)

SM83_CALL_CC_ALL()

//could be same 
int sm84ret(State *s) {
    		pInstruction i = NextInstruction();
    		INSTRUCTION_SET_INFO(3, CALL);
			INSTRUCTION_SET_FLAGS(RET);
			return 0;
}

int sm84reti(State *s) {
    		pInstruction i = NextInstruction();
    		INSTRUCTION_SET_INFO(3, CALL);
			INSTRUCTION_SET_FLAGS(RETI);
			return 0;
}

#define SM83_RET_CC(cc) \
int sm84ret##ccnn (State *s) { \
    		pInstruction i = NextInstruction();\
    		INSTRUCTION_SET_INFO(3, CALL);\
			INSTRUCTION_SET_FLAGS(cc);\
			return 0;\
}

#define SM83_RET_CC_ALL() \
SM83_RET_CC(NZ)\
SM83_RET_CC(Z)\
SM83_RET_CC(NC)\
SM83_RET_CC(C)

SM83_RET_CC_ALL()

#define SM83_RST_T(t) \
int sm84rst##t (State *s) { \
    		pInstruction i = NextInstruction();\
    		INSTRUCTION_SET_INFO(3, CALL);\
			INSTRUCTION_SET_FLAGS(t);\
			return 0;\
}

#define SM83_RST_ALL() \
SM83_RST_T(0) \
SM83_RST_T(1) \
SM83_RST_T(2) \
SM83_RST_T(3) \
SM83_RST_T(4) \
SM83_RST_T(5) \
SM83_RST_T(6) \
SM83_RST_T(7)

SM83_RST_ALL()
