#include <Lpp/Rapi.hpp>
Lpp::Rapi::Rapi(int port){
	this->port = port;
}
void Lpp::Rapi::route(Lpp::string path, std::function<void()> callback){
	auto temp = [&]() -> void {

		std::vector<Lpp::string> pathRules = path.explode("/");
		bool compare = true;
		if(pathRules.size() == 0) compare = false;
		
		for(int i = 0; i < pathRules.size(); i++){
			if(i >= this->pathVect.size() || !(pathRules[i].compare(this->pathVect[i]) == 0)){
				compare = false;
				i = pathRules.size();
			}
		}
		if(compare) callback();
    };
    this->routeFunc.push_back(temp);
}

void Lpp::Rapi::start(){
	Lpp::Http http(this->port);
	http.listen([&]() -> void {
		this->pathVect = http.getPath().explode("/");
		this->params = http.getParams();

		this->response = this->responseDefault;

		for(int i = 0; i < this->routeFunc.size(); i++){
			this->routeFunc[i]();
		}
	
		http.setResponse(this->response);
    });		
}

Lpp::string Lpp::Rapi::getParams(Lpp::string key){
	Lpp::string result;
	if(!this->params[key].empty()) result = this->params[key];
	else this->params.erase(key);

	return result;
}

void Lpp::Rapi::setResponse(Lpp::string response){
	this->response = response;
}
Lpp::string Lpp::Rapi::getResponse(){
	return this->response;
}