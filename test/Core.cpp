#include <Core.hpp>

const char* LppTest::Core::class_name = "";
const char* LppTest::Core::method_name = "";
int LppTest::Core::count = 0;

void LppTest::setClass(const char* name){
	LppTest::Core::class_name = name;
		std::cout << std::endl;
		std::cout << "Starting " << LppTest::Core::class_name << " unit tests ..." << std::endl;
}
void LppTest::setMethod(const char* name){
	LppTest::Core::method_name = name;
	LppTest::Core::count = 1;
	std::cout << std::endl << LppTest::Core::method_name << ":" << std::endl;
}
void LppTest::test(bool result){
	std::cout << LppTest::Core::count << ") ";
	if(result) std::cout << "OK";
	else std::cout << "Error";
	std::cout << std::endl;

	LppTest::Core::count++;
}

void LppTest::end(){
	std::cout << std::endl << "Unit Test End..." << std::endl;
}