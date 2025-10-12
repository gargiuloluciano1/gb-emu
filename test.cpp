#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;

typedef enum {
		on = 1,
		off = 2,
		help = 4,
} Flags;

typedef struct {
		int d;
		int flags;
} Operand;

#define SETFLAGS(flags) flags

int d[] = {0x03, 0x40, 0x80 ,0x40};
int i = 1;
#define ReadNextByteFromMemory()  d[i+1]
#define ReadNextHByteFromMemory() d[i+1]<<4 | d[i+2]

#define OperandSet(r, flags) \
		{r, flags}

int main() {
		int x = 100;
		int y = Flags.help
		//Operand y = OperandSet(ReadNextHByteFromMemory(), on | Flags.help); //101
		printf("%d\n", y);
		return 0;
}
