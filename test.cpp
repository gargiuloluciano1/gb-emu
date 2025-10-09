#include <stdint.h>
typedef uint8_t BYTE;

typedef struct { 
		union {
				BYTE a[7];
				struct {
						BYTE x1;
						BYTE x2;
						BYTE x3;
						BYTE x4;
						BYTE x5;
						BYTE x6;
						BYTE x7;
						BYTE x8;
				};
		};
} A;

A a;
int main() {
		return 0;
}
