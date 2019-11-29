#pragma once

#include "Funcs.h"
#include "Definitions.h"

namespace Assembler {
	void vec_remove_empty(std::vector<std::string>& veccy);
	void str_remove_char(std::string& str, char c);
	bool is_valid_opcode(std::string opname);
	void AssembleToBIN(std::string code, std::string filename);
	long getFileSize(FILE* file);

	Opcode get_op_by_name(std::string opname);
	std::vector<uint32_t> assemble(std::string asmbly, bool debug=false);
	std::vector<uint32_t> LoadBIN(std::string filename);
};