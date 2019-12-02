#include "Assembler.h"

Opcode NULL_OPCODE = {
	"mhm yes nope.",
	0xDEADBEEF,
	(int32_t)0xEADBEEF,
};

std::vector<Opcode> opcodez = {
	{"NOP",  NOP,	0x0},
	{"RET",  RET,	0x0},
	{"PUSH", PUSH,	0x1},
	{"POP",  POP,	0x1},
	{"JMP",  JMP,	0x1},
	{"CALL", CALL,	0x1},
	{"MOV",  MOV,	0x2},
	{"OUT",  OUT,	0x1},
	{"INC",  INC,   0x1},
	{"DEC",  DEC,   0x1},
	{"ADD",  ADD,   0x2},
	{"SUB",  SUB,   0x2},
	{"MUL",  MUL,   0x2},
	{"DIV",  DIV,   0x2},
	{"MOD",  MOD,   0x2},
	{"CMP",  CMP,   0x2},
	{"JE",   JE,    0x1},
	{"HLT",  HLT,   0x0},

	{"AX",   AX,	-0x1},
	{"BX",   BX,	-0x2},
	{"CX",   CX,	-0x3},
	{"DX",   DX,	-0x4},
	{"EX",   EX,	-0x5},
	{"FX",   FX,	-0x6},
};

bool compOpcode(Opcode o1, Opcode o2) {
	return (o1.engrish == o2.engrish &&
		o1.code == o2.code &&
		o1.argc == o2.argc);
}

namespace Assembler {
	void vec_remove_empty(std::vector<std::string>& veccy) {
		for (size_t i = 0; i < veccy.size(); i++) {
			if (veccy[i] == "") {
				veccy.erase(veccy.begin() + i);
			}
		}
	}

	void str_remove_char(std::string& str, char c) {
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] == c) {
				str.erase(str.begin() + i);
			}
		}
	}

	Opcode get_op_by_name(std::string opname) {
		for (auto item : opcodez) {
			if (item.engrish == opname) {
				return item;
			}
		}

		return NULL_OPCODE;
	}

	bool is_valid_opcode(std::string opname) {
		Opcode foundItem = get_op_by_name(opname);

		if (compOpcode(foundItem, NULL_OPCODE)) {
			return false;
		}

		// the found item must be one of the other shits
		if (foundItem.argc <= -0x1) {
			return false;
		}

		return true;
	}

	struct Label {
		std::string name;
		uint32_t offset;
	};

	std::vector<uint32_t> assemble(std::string asmbly, bool debug) {
		std::vector<uint32_t> output;
		std::vector<uint32_t> labels; // funcs / coroutines etc

		auto lines = split(asmbly, "\n");

		for (size_t i = 0; i < lines.size();) {
			auto line = lines[i];

			auto shids = split(line, " ");

			if (!is_valid_opcode(shids[0])) {
				printf("Error(1) on line %d\n", i);
			}

			vec_remove_empty(shids);

			std::vector<std::string> new_vec;

			for (auto shit : shids) {
				auto nshit = shit;
				str_remove_char(nshit, ' ');
				str_remove_char(nshit, ',');
				str_remove_char(nshit, '\t');

				new_vec.push_back(nshit);
			}

			if (shids[0] == '@') {
				labels.push_back(shids[0]);
				continue;
			}


			Opcode mainOperation = get_op_by_name(shids[0]);
			if ((new_vec.size() - 1) != mainOperation.argc) {
				printf("Bad args passed on line %d\n", i);
				break;
			}


			size_t lineCount = 0;
			for (auto code : new_vec) {
				Opcode op = get_op_by_name(code);
				//printf("@@ %s @@\n", code.c_str());

				if (compOpcode(op, NULL_OPCODE)) {
					// assume it's just a value... for now...

					auto num = stoi(code, 0, 16);
					output.push_back(num);
					if (debug) printf("new number: 0x%x\n", num);
					break;
				}

				output.push_back(op.code);
				if (debug) printf("new op/reg: 0x%x\n", op.code);

				lineCount++;
			}

			i++;
		}

		return output;
	}

	void AssembleToBIN(std::string code, std::string filename) {
		auto assembled1 = Assembler::assemble(code);

		std::ofstream nfile(filename);

		for (auto n : assembled1) {
			unsigned char* p = (unsigned char*)&n;
			nfile << p[0];
			nfile << p[1];
			nfile << p[2];
			nfile << p[3];
		}

		nfile.close();
	}

	long getFileSize(FILE* file) {
		long lCurPos, lEndPos;
		lCurPos = ftell(file);
		fseek(file, 0, 2);
		lEndPos = ftell(file);
		fseek(file, lCurPos, 0);
		return lEndPos;
	}

	std::vector<uint32_t> LoadBIN(std::string filename) {
		std::vector<uint32_t> output;

		FILE* file = fopen(filename.c_str(), "rb");;

		if (file == NULL) {
			printf("Failed to load bin %s\n", filename.c_str());
			return output;
		}

		char* buf;
		auto filesize = getFileSize(file);
		buf = new char[filesize];
		fread(buf, filesize, 1, file);

		for (int i = 0; i < filesize; i += 4) {
			auto next_num = 0x0;
			char* c = new char[4];
			c[0] = buf[i];
			c[1] = buf[i + 1];
			c[2] = buf[i + 2];
			c[3] = buf[i + 3];
			next_num = *((uint32_t*)c);

			output.push_back(next_num);
		}

		return output;
	}
};
