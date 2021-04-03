#ifndef LPP_ARRAY
#define LPP_ARRAY

#include <vector>
#include <string>

//DEBUG
#include <iostream>

namespace Lpp{
	template <class T>
	class Array{
		public:
			Array(T element, size_t position);
			//Array();
			void Lpp::Array::insert(std::string name, T value);
			T& operator[](int);
			T& operator[](std::string); 
		private:
			std::vector<std::string> key;
			std::vector<T> value;
			int size;
	};
}
#endif