# General Notes on Instruction Set Architecture

Some instructions, relative to same group, have flags inside the opcode that differentiate them (ex. ADD and SUB or the logical operations)
Could use this to make more general functions in dispatch routine. Giving flags to the Instruction Template Struct used by the interpreter.

Instructions are generally composed of two Operands. Operand can be either a register (1 or 2 bytes) or an immediate. An operand can either
be interpreted as data (immediate) or as a register index. the data Inside the register can represent either the data itself or pointer to data

Should Name for Instruction just be the opcode? or keep a sort of mnemonics syntax

# Fetching Instructions for Operands in I/O

Important, instructions like ld a, nn put the next two byte in little or big endian? need to check

Rewrite all functions usign preprocessor? Instead of assigning 1:n for routines might just make every function and "automate" it with preprocessor?
