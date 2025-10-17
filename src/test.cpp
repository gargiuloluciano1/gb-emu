#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;

#define A 001
#define B 002
#define C 003
#define D 004
#define E 005
#define F 006
#define H 007

typedef struct {
		int x;
} Instruction;

#define sm64_fake_(op, m) \
int sm64_fake##op##m(Instruction *i) { \
		i->x = m; \
		return 0;\
}
#define sm64_fake_define_op(op) \
		sm64_fake_(op, A) \
		sm64_fake_(op, B) \
		sm64_fake_(op, C) \
		sm64_fake_(op, D) \
		sm64_fake_(op, E) \
		sm64_fake_(op, F) \
		sm64_fake_(op, H) \

#define sm64_fake_define_all() \
		sm64_fake_define_op(op)

sm64_fake_define_all()

int main() {
		Instruction i;
		sm64_fakeopB(&i);
		sm64_fakeopC(&i);
		
		//Operand y = OperandSet(ReadNextHByteFromMemory(), on | Flags.help); //101
		printf("%d\n", i.x);
		return 0;
}
