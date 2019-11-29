#include "Assembler.h"
#include "Emulation.h"

int main(int argc, char** argv) {
	CPU* system = new CPU();
	
	std::ifstream file("fuckery.asm");
	std::string str;
	std::string file_contents;
	while (std::getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}

	printf("Assembling...\n");
	Assembler::AssembleToBIN(file_contents, "fuck.bin");      // save binary
	
	auto bytecode = Assembler::LoadBIN("fuck.bin");           // load binary

	printf("\nExecuting...\n");
	auto result = system->ExecuteProgram(bytecode, 0x0);

	printf("Program returned: 0x%x\n", result);
	
	
	return getchar();
}
