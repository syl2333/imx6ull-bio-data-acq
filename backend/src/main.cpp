#include <iostream>
#include "httplib.h"
#include "sqlite3.h"

#include "db.h"
#include "log.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void hello_handler(const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello, World!", "text/plain");
}



int main()
{
    //log4cpp_init();
    Logger::getInstance().info("This is an info log message.");
    SQLiteWrapper db("local.db");
    db.init_tables();

    json parsedBody;
 

    httplib::Server Server;

    //解决跨域问题
    Server.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) -> httplib::Server::HandlerResponse {
        // 添加CORS相关响应头
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

        if (req.method == "OPTIONS") {
            res.status = 204;
            return httplib::Server::HandlerResponse::Handled; // 不继续执行后续的请求处理器
        }

        return httplib::Server::HandlerResponse::Unhandled; // 继续执行后续的请求处理器
    });
    Server.Get("/hello",hello_handler);
    Server.Post("/login", [&db,&parsedBody](const httplib::Request &req, httplib::Response &res) {
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");
        Logger::getInstance().infoStream() << req.body << username;
        try {
            parsedBody = json::parse(req.body);
        } catch (const json::parse_error& e) {
            Logger::getInstance().errorStream() << "JSON解析错误: " << e.what();
        }
        // 处理用户名和密码，例如验证或存储等
        Logger::getInstance().infoStream() << "Username: " << parsedBody["username"];
        Logger::getInstance().infoStream() << "Password: " << parsedBody["password"];
        auto ret = db.verifyUserPassword(username,password);
        if(ret)
        {
            // 返回响应
            res.set_content("Login request received", "text/plain");
        }
        
    });
    std::cout << "httplib listening on http://127.0.0.1:8000" << std::endl;
    Server.listen("localhost",8000);


    return 0;
}