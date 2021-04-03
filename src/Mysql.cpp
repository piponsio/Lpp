#include <Lpp/Mysql.hpp>

Lpp::Mysql* Lpp::Mysql::instance = 0;
Lpp::string Lpp::Mysql::server_default = "localhost";
Lpp::string Lpp::Mysql::user_default = "pbs";
Lpp::string Lpp::Mysql::pass_default = "";
Lpp::string Lpp::Mysql::db_default = "csDB";
unsigned int Lpp::Mysql::port_default = 3306; 

Lpp::Mysql::Mysql(){}

Lpp::Mysql::~Mysql(){
    this->connection.disconnect();
}

Lpp::Mysql* Lpp::Mysql::init(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port){
    if(NULL == Lpp::Mysql::instance){
        Lpp::Mysql::instance = new Lpp::Mysql();
        (*Lpp::Mysql::instance).connect(server, user, pass, db, port);
    }
    return Lpp::Mysql::instance;      
}

Lpp::Mysql* Lpp::Mysql::init(Lpp::string db){
    return Lpp::Mysql::init(Lpp::Mysql::server_default, Lpp::Mysql::user_default, Lpp::Mysql::pass_default, db, Lpp::Mysql::port_default);
}

Lpp::Mysql* Lpp::Mysql::init(){
    return Lpp::Mysql::init(Lpp::Mysql::server_default, Lpp::Mysql::user_default, Lpp::Mysql::pass_default, Lpp::Mysql::db_default, Lpp::Mysql::port_default);
}

Lpp::Mysql* Lpp::Mysql::newSql(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port){
    Lpp::Mysql* instance = new Lpp::Mysql();
    (*instance).connect(server, user, pass, db, port);
    return (instance);      
}

bool Lpp::Mysql::connect(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port){
    bool result = false;

    this->server = server;
    this->user = user;
    this->pass = pass;
    this->db = db;
    this->port = port;

    mysqlpp::Connection conn(false);
    this->connection =  conn;

    char* server_temp = &this->server[0];
    char* user_temp = &this->user[0];
    char* pass_temp = &this->pass[0];

    result = this->connection.connect(NULL, server_temp, user_temp, pass_temp, this->port);

    if(!result) std::cout << "Fallo al conectarse a la BD: " << this->connection.error() << std::endl;
    else this->simpleQuery("use "+this->db);

    return result;
}


bool Lpp::Mysql::query(Lpp::string queryStr){

    //Escape de caracteres oficiales !!!
    mysqlpp::StoreQueryResult result;
    mysqlpp::Query query = this->connection.query(queryStr);
    
    return (this->result = query.store());
}


bool Lpp::Mysql::simpleQuery(Lpp::string queryStr){
    //Escape de caracteres oficiales !!!

    mysqlpp::Query query  = this->connection.query(queryStr);
    this->result.clear();
    return (query.execute());
}

int Lpp::Mysql::numRows(){
    return this->result.size();
}

mysqlpp::StoreQueryResult Lpp::Mysql::getResult(){
    return this->result;
}
Lpp::string Lpp::Mysql::getResult(int row, const char* col_name){
    Lpp::string result = Lpp::string(this->result[row][col_name].data(),this->result[row][col_name].size());
    return result;
}
mysqlpp::StoreQueryResult Lpp::Mysql::getResult(Lpp::string queryStr){
    this->query(queryStr);
    return this->result;
}


/*
mysqlpp::Connection conn(false);
   char server[] = "localhost";
   char user[]   = "pbs";  // O cualquier usuario
   char pass[]   = "";

   if (conn.connect(NULL, server, user, pass))
   {
      // string consulta = "select * from ins_institutos";
     std::string consulta="SHOW DATABASES";
      mysqlpp::Query query = conn.query(consulta);
      if (mysqlpp::StoreQueryResult res = query.store())
      {
    std::cout << "Bases de datos encontradas: "<< res.num_rows()<< std::endl;
         if (res.num_rows() > 0)
       {
         bool poesiadb=false;
         // std::cout <<res[0]["nombre"] <<  std::endl;
         for (mysqlpp::StoreQueryResult::iterator it=res.begin(); it!=res.end(); ++it)
           {
         if ((it)->at(0)=="poesiadb")
           {
             poesiadb=true;
             break;
           }
         // Si queremos visualizar las bases de datos...
         std::cout <<"Base de datos: "<< (it)->at(0) <<  std::endl; // Se puede hacer con (*it)[0] pero la documentación dice que es más lento
           }
         if (poesiadb)
           {
         // Miramos los contenidos de la tabla
         std::cout << "La base de datos se encuentra" <<  std::endl;
         query.reset();
         query<<"SELECT * FROM `poesiadb`.`test`";
         res=query.store();
         if (res.num_rows() >0)
           {

             for (mysqlpp::StoreQueryResult::iterator it=res.begin(); it!=res.end(); ++it)
               {
             for (unsigned i=0; i<res.num_fields(); i++)
               std::cout <<res.field_name(i)<<" = "<< (it)->at(i) <<  std::endl; // Se puede hacer con (*it)[0] pero la documentación dice que es más lento

             std::cout <<  std::endl;
               }
             
           }
         else
           std::cout << "No se han obtenido datos" <<  std::endl;
           }
         else
           {
         // Lo construimos todo
         std::cout << "Creando base de datos" <<  std::endl;
         if (conn.create_db("poesiadb"))
           {
             std::cout << "Seleccionando base de datos" <<  std::endl;
             if (conn.select_db("poesiadb"))
               {
             std::cout << "Creando tabla" <<  std::endl;
             query.reset();
             query=conn.query("CREATE TABLE IF NOT EXISTS `poesiadb`.`test` ("
                      "`id` bigint(20) NOT NULL AUTO_INCREMENT,"
                      "`blog` varchar(100) NOT NULL,"
                      "`url` varchar(255) NOT NULL,"
                      "PRIMARY KEY (`id`)"
                      ") ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;");          
             if (query.execute())
               {
                 query.reset();
                 query << "INSERT INTO `test` VALUES (NULL, 'Poesia binaria', 'https://poesiabinaria.net/');";
                 if(!query.execute())
                   std::cout << "Fallo al introducir datos"<< std::endl;
                 query.reset();
                 query << "INSERT INTO `test` VALUES (NULL, 'Clase 911', 'http://clase911.com/');";
                 if(!query.execute())
                   std::cout << "Fallo al introducir datos"<< std::endl;
                 query.reset();
                 query << "INSERT INTO `test` VALUES (NULL, 'Ubuntizados', 'http://ubuntizados.com/');";
                 if(!query.execute())
                   std::cout << "Fallo al introducir datos"<< std::endl;
               }
             else
               std::cout << "Error al crear tabla"<< std::endl;
               }
             else
               std::cout << "Fallo al seleccionar la base de datos" <<  std::endl;
           }
         else
           std::cout << "Fallo al crear base de datos" <<  std::endl;
           }
       }
     else
       std::cout << "Fallo al obtener bases de datos" <<  std::endl;
      }
      conn.disconnect();
   }
   else
     std::cout <<"Fallo al conectarse a la BD: "<<conn.error()<< std::endl;
*/