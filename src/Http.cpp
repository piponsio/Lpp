#include <Lpp/Http.hpp>

Lpp::Http::Http(int port){
    this->port = port;
    int one = 1;
    this->sin_len = sizeof(cli_addr);
    memset(this->buffer, 0, 1024);
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (this->sock < 0) err(1, "can't open socket");
    setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    this->port = port;
    this->svr_addr.sin_family = AF_INET;
    this->svr_addr.sin_addr.s_addr = INADDR_ANY;
    this->svr_addr.sin_port = htons(this->port);

    if (bind(this->sock, (struct sockaddr *) &this->svr_addr, sizeof(this->svr_addr)) == -1) {
        close(this->sock);
        err(1, "Can't bind");
    }

}

void Lpp::Http::listen(std::function<void()> callback){

    ::listen(this->sock, 5);
    while (1) {
        this->client_fd = accept(this->sock, (struct sockaddr *) &this->cli_addr, &this->sin_len);
        this->valread = read( this->client_fd , this->buffer, 1024);

        std::cout << this->buffer << std::endl;

        this->request();
        callback();

        if (this->client_fd == -1) {
            perror("Can't accept");
            continue;
        }

        char response_temp[this->response.size()];
        strcpy(response_temp, this->response.c_str()); 
        
        ::write(this->client_fd, response_temp, sizeof(response_temp) - 1);
        ::close(this->client_fd);
        memset(this->buffer, 0, 1024);
    }

}
void Lpp::Http::request(){
    Lpp::string buffer_temp(this->buffer);
    for(int i = 0; i < this->methods.size(); i++){
        std::string::size_type init_method = buffer_temp.find(this->methods[i]);
        if( init_method != std::string::npos && init_method == 0){
            this->method = this->methods[i];
            i = this->methods.size();
        }
    }
    if(this->method.size() != 0){
/*
        this->request_url = buffer_temp.substring(this->method+" ", " HTTP");
        this->path = Lpp::string::substring(" "+this->request_url, " ", "?");
        if(this->path.size() == 0) this->path = this->request_url;
        this->str_params = Lpp::string::substring(this->request_url+" ", "?", " ");
        this->version = std::stof(buffer_temp.substring("HTTP/", "\r\n"));

        std::string content_length = buffer_temp.substring("Content-Length: ", "\r\n");
        if(content_length.size() == 0) this->content_length = 0;
        else this->content_length = std::stoi(content_length);

        this->message = buffer_temp.substring("\r\n\r\n", "\r\n");
*/
        
        this->request_url = buffer_temp.substr(this->method+" ", " HTTP");
        this->path = Lpp::string::substr(" "+this->request_url, " ", "?");
        if(this->path.size() == 0) this->path = this->request_url;
        this->str_params = Lpp::string::substr(this->request_url+" ", "?", " ");
        this->version = std::stof(buffer_temp.substr("HTTP/", "\r\n"));

        std::string content_length = buffer_temp.substr("Content-Length: ", "\r\n");
        if(content_length.size() == 0) this->content_length = 0;
        else this->content_length = std::stoi(content_length);

        this->message = buffer_temp.substr("\r\n\r\n", "\r\n");

        if(this->method.compare("POST") == 0 && this->str_params.size() == 0) this->str_params = this->message;
        if(this->str_params.size() > 0){
            std::vector<Lpp::string> params = this->str_params.explode("&");
            std::vector<Lpp::string> key_value;
            for(int i = 0; i < params.size(); i++){
                key_value = params[i].explode("=");
                this->params[key_value[0]] = key_value[1];
                key_value.clear();
            }
        }
    }
}
Lpp::string Lpp::Http::getUrl(){
    return this->request_url;
}
Lpp::string Lpp::Http::getPath(){
    return this->path;
}
Lpp::string Lpp::Http::getMessage(){
    return this->message;
}
Lpp::string Lpp::Http::getResponse(){
    return this->response;
}
std::map<Lpp::string, Lpp::string> Lpp::Http::getParams(){
    return this->params;
}
Lpp::Http::~Http(){

}

void Lpp::Http::setResponse(Lpp::string response){
    this->response = response;
}