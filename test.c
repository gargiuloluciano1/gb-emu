#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main() {
						//   1    6
		int op = 0xCE; //11 00 1 110
		BYTE op1 = (op&0x38)>>3;
		BYTE op2 = op&0x07;

		printf("op1 :%2x\n", op1);
		printf("op2 :%2x\n", op2);

		return 0;
}
