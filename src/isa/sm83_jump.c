#include "emulator.h"
typedef Instruction* pInstruction;

int sm83jpnn (State *s) {
    		pInstruction i = NextInstruction(); 
    		INSTRUCTION_SET_INFO(3, JUMP); 
			INSTRUCTION_SET_FLAGS(JP); 
    		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, direct);
			return 0;
}
#define SM83_JP_CC_(cc) \
int sm83jp##ccnn (State *s) { \
    		pInstruction i = NextInstruction(); \
    		INSTRUCTION_SET_INFO(3, JUMP);  \
			INSTRUCTION_SET_FLAGS(cc);  \
    		i->rd = OperandSet(ReadNextHWordFromMemory(), 1, direct); \
			return 0; \
}

#define SM83_JP_CC_ALL() \
SM83_JP_CC_(NZ) \
SM83_JP_CC_(Z) \
SM83_JP_CC_(NC) \
SM83_JP_CC_(C)

SM83_JP_CC_ALL()

int sm83jre (State *s) {
    		pInstruction i = NextInstruction();
    		INSTRUCTION_SET_INFO(2, JUMP); 
			INSTRUCTION_SET_FLAGS(JP); 
    		i->rd = OperandSet(ReadNextByteFromMemory(), 1, indexed);
			return 0;
}

int sm83jphl (State *s) {
    		pInstruction i = NextInstruction();
    		INSTRUCTION_SET_INFO(1, JUMP); 
			INSTRUCTION_SET_FLAGS(JP); 
    		i->rd = OperandSet(HL, 0, indirect);
			return 0;
}
