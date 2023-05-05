#ifndef __DB_H__
#define __DB_H__

#include <iostream>
#include <string>
#include <string.h>
#include "sqlite3.h"


class SQLiteWrapper {
    public:
        SQLiteWrapper(const std::string& db_name);
        ~SQLiteWrapper();

        bool init_tables();
        bool verifyUserPassword(std::string user,std::string passwd);
        std::string query_password_by_name(const std::string &name);
    private:
        std::string m_db_name;
        sqlite3* m_db = nullptr;

        bool open(const std::string& db_name);
        bool execute(const std::string& sql);
        void close();

        
};






#endif