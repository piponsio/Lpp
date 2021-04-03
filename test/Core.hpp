#ifndef LPPTESTCORE
#define LPPTESTCORE

#include <iostream>

namespace LppTest{

	class Core{
	public:
		static const char* class_name;
		static const char* method_name;
		static int count;
	};	

	void setClass(const char* name);
	void setMethod(const char* name);
	void test(bool result);	
	void end();	
}
#endif