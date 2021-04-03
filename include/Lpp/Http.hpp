#ifndef LPP_HTTP
#define LPP_HTTP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <cstring>

#include <Lpp/String.hpp>

//DEBUG
#include <iostream>

namespace Lpp{
	class Http{
		public:
			Http(int port);
			~Http();
			void request();
			void listen(std::function<void()> callback);

			Lpp::string getUrl();
			Lpp::string getPath();
			Lpp::string getMessage();
			Lpp::string getResponse();
			std::map<Lpp::string, Lpp::string> getParams();

			void setResponse(Lpp::string response);
		private:
			Lpp::string response;
			char buffer[1024];
			int port;
			int sock;
			int client_fd;
			socklen_t sin_len;
			int valread;
			struct sockaddr_in svr_addr, cli_addr;

			Lpp::string method;
			Lpp::string request_url;
			Lpp::string path;
			Lpp::string str_params;
			std::map<Lpp::string, Lpp::string> params;
			float version;
			int content_length;
			Lpp::string message;

			std::vector<Lpp::string> methods = {"OPTIONS", "GET", "HEAD", "POST", "PUT", "DELETE", "TRACE"};
	};
}
#endif