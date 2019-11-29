#pragma once

#ifndef DEFINITIONZ_H
#define DEFINITIONZ_H

#include <unordered_map>
#include <string>

// Memory setup
#define STACK_SIZE 256								 // how much space we can allocate in the RAM for the stack
#define RAM_SEG_SIZE 64								 // each addressable ram segment
#define RAM_SIZE (RAM_SEG_SIZE * 32) + (STACK_SIZE)  // size of ram overall
#define INT_QUIT (1 << 1)

// List of valid instructions
#define NOP  0x0
#define RET  0x1
#define PUSH 0x2
#define POP  0x3
#define JMP  0x4
#define CALL 0x5
#define MOV  0x6
#define OUT  0x7 // output something
#define INC  0x8
#define DEC  0x9
#define ADD  0xA
#define SUB  0xB
#define MUL  0xC
#define DIV  0xD
#define MOD  0xE
#define CMP  0xF
#define JE   0x10
#define HLT  0x11

#define RAM_REGS_OFFSET (RAM_SIZE - STACK_SIZE)
#define AX RAM_REGS_OFFSET - 0x2
#define BX RAM_REGS_OFFSET - 0x3
#define CX RAM_REGS_OFFSET - 0x4
#define DX RAM_REGS_OFFSET - 0x5
#define EX RAM_REGS_OFFSET - 0x6
#define FX RAM_REGS_OFFSET - 0x7

struct Opcode {
	std::string		engrish;
	uint32_t		code;
	int32_t			argc;
};

extern Opcode NULL_OPCODE;

bool compOpcode(Opcode o1, Opcode o2);

extern std::vector<Opcode> opcodez;

//#define SP RAM_REGS_OFFSET - 0x8
//#define IP RAM_REGS_OFFSET - 0x9
//#define IF RAM_REGS_OFFSET - 0xA

#endif