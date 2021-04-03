#include <Lpp/String.hpp>

Lpp::string Lpp::string::substr(size_t init, size_t end){
    return this->std::string::substr(init, end);
}

Lpp::string Lpp::string::substr(Lpp::string init, Lpp::string end){
    return Lpp::string::substr(*this, init, end);
}

Lpp::string Lpp::string::substr(Lpp::string string, Lpp::string init, Lpp::string end){
    Lpp::string result;

    int init_pos = string.find(init);
    int end_pos = string.find(end, init_pos);
    
    if(init_pos == std::string::npos || end_pos == std::string::npos) result = "";
    else{
        int init_result = init_pos + init.size();
        int len_result = end_pos - init_result; 
        result = string.std::string::substr(init_result, len_result);    
    }
    return result;
}

/*
Lpp::string Lpp::string::substring(Lpp::string init, Lpp::string end){
    Lpp::string result;

    int init_pos = this->find(init);
    int end_pos = this->find(end, init_pos);
    
    if(init_pos == std::string::npos || end_pos == std::string::npos) result = "";
    else{
        int init_result = init_pos + init.size();
        int len_result = end_pos - init_result; 
        result = std::string.substr(init_result, len_result);    
    }
    return result;
}
*/
std::vector<Lpp::string> Lpp::string::explode(Lpp::string delim){
    std::vector<Lpp::string> result;
    Lpp::string temp;
    int init_pos = 0;
    int end_pos = 0;
    
    while(init_pos != std::string::npos){
        end_pos = this->find(delim, init_pos);

        if(end_pos == std::string::npos && init_pos == 0){ //no existe el delimitador
            temp = *this;
        }
        else if(end_pos == std::string::npos && init_pos != 0 && init_pos != std::string::npos){ //ultimo substr del explode
            temp = this->substr(init_pos, this->size());
        }
        else{
            temp = this->substr(init_pos, end_pos - init_pos);
        }
        if(!temp.empty()) result.push_back(temp);

        if(end_pos != std::string::npos) init_pos = end_pos + delim.size();
        else init_pos = end_pos;
    }
    return result;
}

bool Lpp::string::isInt(){
    bool result = true;
    if(this->empty()) result = false;
    for(Lpp::string::iterator it = this->begin(); it != this->end(); it++){
        if( !std::isdigit(*it) && !(*it == 45 && it == this->begin()) ){
            result = false;
            it = this->end()-1;
        }
    }

    return result;
}

bool Lpp::string::isFloat(){
    bool result = true;
    bool dotLock = false;
    if(this->empty()) result = false;
    for(Lpp::string::iterator it = this->begin(); it != this->end(); it++){
        if(!std::isdigit(*it) && ( !(static_cast<int>(*it) == 45 && it == this->begin()) && !(static_cast<int>(*it) == 46 && !dotLock) ) ){
            result = false;
            it = this->end()-1;
        }
    }

    return result;
}

int Lpp::string::toInt(){
    int result = 0;

    if(this->isInt()) result = std::stoi(*this);

    return result;
}

float Lpp::string::toFloat(){
    Lpp::string temp = *this;
    float result = 0;

    if(this->isInt()) temp += ".0";
    if(this->isFloat()) result = std::stof(temp);

    return result;
}