#include <iostream>
#include "httplib.h"
#include "sqlite3.h"
//#include "sqlite3ext.h"

void hello_handler(const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello, World!", "text/plain");
}

sqlite3* db;
int rc;

int main()
{
    char* errMsg = nullptr;
    rc = sqlite3_open("local.db",&db);

       const char* createTableSql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT NOT NULL);";
    rc = sqlite3_exec(db, createTableSql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // 插入数据
    const char* insertDataSql = "INSERT INTO users (name) VALUES ('Alice');";
    rc = sqlite3_exec(db, insertDataSql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // 查询数据
    // const char* selectDataSql = "SELECT * FROM users;";
    // rc = sqlite3_exec(db, selectDataSql, callback, 0, &errMsg);
    // if (rc != SQLITE_OK) {
    //     std::cerr << "SQL error: " << errMsg << std::endl;
    //     sqlite3_free(errMsg);
    // }

    // 关闭数据库连接
    sqlite3_close(db);

    httplib::Server Server;
    Server.Get("/",hello_handler);
    std::cout << "httplib listening on http://127.0.0.1:8000" << std::endl;
    Server.listen("localhost",8000);


    return 0;
}