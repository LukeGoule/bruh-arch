#include "Emulation.h"

CPU::CPU() {
	this->RAM = new uint32_t[RAM_SIZE];
	this->SP = 0x0;
	this->IP = 0x0;
	this->IF = 0x0;

	for (int x = 0; x < RAM_SIZE; x++)
		RAM[x] = NOP;
}

CPU::~CPU() {

}

int CPU::ExecuteProgram(std::vector<uint32_t> program, uint32_t moveto) {
	this->LoadProgram(program, moveto);

	return this->ExecuteProgram(moveto);
}

int CPU::ExecuteProgram(uint32_t startpos) {
	this->IP = startpos;

	uint32_t ret_val = 0;
	uint32_t value, addy, quit = 0, condition = 0;
	uint32_t instruction;

	while (!quit) {
		instruction = this->RAM[this->IP];

		switch (instruction) {
		case NOP:
			quit = 1;
			ret_val = -1;
			break;

		case JMP:
			this->IP = this->RAM[this->IP + 1];
			break;

		case OUT:
			value = this->RAM[this->RAM[this->IP + 1]]; // pointers caught me actin strange
			printf("OUT: 0x%x\n", value);
			this->IP += 2;
			break;

		case MOV:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] = value;

			this->IP += 3;
			break;

		case INC:
			addy = this->RAM[this->IP + 1];

			this->RAM[addy] += 1;
			this->IP += 2;
			break;

		case DEC:
			addy = this->RAM[this->IP + 1];

			this->RAM[addy] -= 1;
			this->IP += 2;
			break;

		case ADD:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] += value;
			this->IP += 3;

			break;

		case SUB:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] -= value;
			this->IP += 3;

			break;

		case MUL:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] *= value;
			this->IP += 3;

			break;

		case DIV:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] /= value;
			this->IP += 3;

			break;

		case MOD:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			this->RAM[addy] %= value;
			this->IP += 3;

			break;

		case CMP:
			addy = this->RAM[this->IP + 1];
			value = this->RAM[this->IP + 2];

			if (this->RAM[addy] == value) {
				condition = 1;
			}
			else {
				condition = 0;
			}

		case JE:
			addy = this->RAM[this->IP + 1];

			if (condition) {
				this->IP = addy;
				condition = !condition;
			}
			else {
				this->IP += 2;
			}
			break;

		case HLT:
			quit = 1;
			break;

		default:
			this->IP += 1;
			break;
		}
	}

	return ret_val;
}

void CPU::LoadProgram(std::vector<uint32_t> program, uint32_t position) {
	for (size_t i = 0; i < program.size(); i++) {
		this->RAM[position + i] = program[i];
	}
}