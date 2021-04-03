#ifndef LPP_RAPI
#define LPP_RAPI

#include <string>
#include <functional>

#include <Lpp/String.hpp>
#include <Lpp/Http.hpp>

namespace Lpp{
	class Rapi{
		public:
			Rapi(int port); 
			void route(Lpp::string path, std::function<void()> callback);
			void start();
			
			Lpp::string getParams(Lpp::string key);

			Lpp::string getResponse();
			void setResponse(Lpp::string response);
		private:
			int port;
			std::map<Lpp::string, Lpp::string> params;
			Lpp::string response;
			Lpp::string responseDefault = 
				"HTTP/1.1 200 OK\r\n"
			    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
			    "<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
			    "<style>body { background-color: #111 }"
			    "h1 { font-size:4cm; text-align: center; color: black;"
			    " text-shadow: 0 0 2mm red}</style></head>"
			    "<body><h1>Default</h1></body></html>\r\n";

			std::vector<Lpp::string> pathVect;
			std::vector<std::function<void()>> routeFunc;		
	};
}
#endif