#ifndef LPP_STRING
#define LPP_STRING

#include <vector>
#include <string>

//DEBUG
#include <iostream>

namespace Lpp{

	class string: public std::string{
		public:
			string() : std::string(){}
			string(const std::string& str) : std::string(str){}
			string(const std::string& str, size_t pos, size_t len = std::string::npos) : std::string(str, pos, len){}

			string(const char* s) : std::string(s){}
			string(const char* s, size_t n) : std::string(s, n){}
			string(size_t n, char c) : std::string(n, c){}
			template <class InputIterator>
			  string (InputIterator first, InputIterator last) : std::string (first, last){}
			string(std::initializer_list<char> il) : std::string(il){}
//			string(string&& str) noexcept : std::string(str){}

			Lpp::string substr(size_t init, size_t end);
			Lpp::string substr(Lpp::string init, Lpp::string end);
			static Lpp::string substr(Lpp::string string, Lpp::string init, Lpp::string end);

			std::vector<Lpp::string> explode(Lpp::string delim);

			bool isInt();
			bool isFloat();
			int toInt();
			float toFloat();
	};
}
#endif