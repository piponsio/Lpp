#ifndef LPP_MYSQL
#define LPP_MYSQL

#include <mysql++/mysql++.h>
#include <Lpp/String.hpp>

namespace Lpp{
	class Mysql{

		public:
			typedef mysqlpp::StoreQueryResult Result;
			
			~Mysql();

			static Lpp::Mysql* init(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port = 3306);
			static Lpp::Mysql* init(Lpp::string db);
			static Lpp::Mysql* init();
			static Lpp::Mysql* newSql(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port = 3306);

			bool query(Lpp::string queryStr);
			bool simpleQuery(Lpp::string queryStr);

			int numRows();
			Lpp::string getResult(int row, const char* col_name);
			mysqlpp::StoreQueryResult getResult();
			mysqlpp::StoreQueryResult getResult(Lpp::string queryStr);
			//mysqlpp::String getResult(int row, const char* col_name);

		private:
			Mysql(); 
			Mysql(const Lpp::Mysql & obj);

			static Lpp::Mysql* instance;
			
			static Lpp::string server_default;
			static Lpp::string user_default;
			static Lpp::string pass_default;
			static Lpp::string db_default;
			static unsigned int port_default; 

			Lpp::string server;
			Lpp::string user;
			Lpp::string pass;
			Lpp::string db;
			unsigned int port = 0;

			mysqlpp::Connection connection;
			mysqlpp::StoreQueryResult result;

			bool connect(Lpp::string server, Lpp::string user, Lpp::string pass, Lpp::string db, unsigned int port = 3306);
			//mysqlpp::StoreQueryResult result;
			//mysqlpp::Query gansho;// -> Aqui está el error por el tipo de dato
	};
}
#endif