#include <Lpp/array.hpp>

template <class T>

Lpp::Array<T>::Array{*}(T element, size_t position){
    this->value.push_back(element);
}
void Lpp::Array<T>::insert(std::string name, T value){
    this->key.push_back(name);
    this->value.push_back(value);
}
T& Array::operator[](int index){ 
    if (index >= this->size) { 
        //cout << "Array index out of bound, exiting"; 
        //exit(0);
    } 
    return this->value[index]; 
}
T& Array::operator[](std::string key){
    T result;
    for(int i = 0; i < this->key.size(); i++){
        if(this->key[i].compare(key) == 0){
            i = this->key.size();
            result = this->value[i];
        }
    }
    return result; 
}