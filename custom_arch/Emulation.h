#pragma once

#include "Definitions.h"

class CPU {
private:
	uint32_t* RAM;

	// registers
	union {
		uint32_t SP; // stack pointer
		uint32_t IP; // instruction pointer / program counter
		uint32_t IF; // interrupt flag - use for errors
	};
public:

	CPU();

	~CPU();

	int ExecuteProgram(std::vector<uint32_t> program, uint32_t moveto);
	int ExecuteProgram(uint32_t startpos);
	void LoadProgram(std::vector<uint32_t> program, uint32_t position);
};