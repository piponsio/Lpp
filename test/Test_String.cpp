#include <Core.hpp>
#include <Test_String.hpp>

using namespace LppTest;

void LppTest::TestString(){
	Lpp::string string_test("Esta es otra prueba por que la num 2241 murio y no quedo ni el 0.045 xxd");
	Lpp::string string_test2("0303426");
	Lpp::string string_test3 = string_test2 + ".5";
	Lpp::string string_test4("-0303426");

	setClass("Lpp::string");

	setMethod("Lpp::string substr(size_t,size_t)");
	test(string_test.substr(13, 6).compare("prueba") == 0);
	test(string_test.substr(22, 5).compare("r que")  == 0);

	setMethod("Lpp::string substr(Lpp::string,Lpp::string)");
	test(string_test.substr("prueba", "2241").compare(" por que la num ")  == 0);
	test(string_test.substr(" 2241 ", " y no").compare("murio")  == 0);

	setMethod("Lpp::string isInt()");
	test(string_test2.isInt());
	test(!string_test.isInt());
	test(string_test.substr("num ", " murio").isInt());
	test(string_test4.isInt());

	setMethod("Lpp::string isFloat()");
	test(string_test3.isFloat());
	test(!string_test.isFloat());
	test(string_test.substr("ni el ", " xxd").isFloat());

	end();
}