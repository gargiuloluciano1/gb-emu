#ifndef EMULATOR_H
#define EMULATOR_H

//(NOTE) using compiling with c++ because of future things

#include <stdint.h>
typedef uint8_t  BYTE;
typedef uint16_t HWORD;
typedef uint32_t WORD;

#define Kilobit(n) (n)*128

#ifdef DEBUG
#define ASSERT(exp) \
if (exp) {\
	fprintf("ASSERT at %ld\n", __LINE__); \
	((char*)0) = 0; \
}
#else
#define ASSERT(exp)
#endif
// ===SM83 Architecture===

//TODO should implement a fake communication with cpu and system?

// TODO add flags
// flags for load 8b instruction 
//
// OP: xyz abc de
//
// where x=1
// y = ^IMM
// cde = 010b is special mode for interpretation, means y = 1
typedef enum {
		IMM =0x80, //0x 01000000b
		DEREF1= 0x40, //needs to be read as a pointer
		DEREF2= 0x20, //needs to be read as a pointer
} SM83_LD8B_FLAGS;

typedef struct {
	BYTE op;
	BYTE len; // one to three, useful for spc to tpc
	BYTE type; //example arithmetic only differ for flags set
	BYTE flags;
	HWORD r1;
	HWORD r2;
	void* dispatch;
} sm83_instruction;

//sm83 instructions might have this as a prefix
#define is_prefix(op) (op)==0xCD

// Global structure
//TODO look into singleton pattern
typedef struct {
		union {
				BYTE r8[7];
				struct {
						BYTE A;
						BYTE B;
						BYTE C;
						BYTE D;
						BYTE E;
						BYTE H;
						BYTE L;
				};
		};
		union {
				HWORD r16[5];
				struct {
						HWORD HL;
						HWORD BC;
						HWORD DE;
						HWORD SP;
						HWORD PC;
				};
		};
		//TODO
		// internal ram area (like cache)

} sm83_cpu;

typedef struct {
	//interpreter
		//TODO for now is static and only 128 for testing
	sm83_instruction code[128];
	BYTE tpc;
	//cpu area
	sm83_cpu cpu;
	//memory space 
} State;

#endif

