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
        try {
            parsedBody = json::parse(req.body);
        } catch (const json::parse_error& e) {
            Logger::getInstance().errorStream() << "JSON解析错误: " << e.what();
        }
        // 处理用户名和密码，例如验证或存储等
        auto username = parsedBody["username"];
        auto password = parsedBody["password"];
        Logger::getInstance().infoStream() << "Username: " << username;
        Logger::getInstance().infoStream() << "Password: " << password;
        auto ret = db.verifyUserPassword(username,password);

        json responseJson;
        //res.set_content_type("application/json");
        res.set_header("Content-Type", "application/json");
        if(ret)
        {
            responseJson["status"] = "success";
            responseJson["message"] = "登陆成功";
            // 返回响应
            res.set_content(responseJson.dump().c_str(), "application/json");
            return res;
        }
        res.status = 401;
        responseJson["status"] = "error";
        responseJson["message"] = "登陆失败，用户名或密码错误";
        res.set_content(responseJson.dump().c_str(), "application/json");
        return res;
    });
    std::cout << "httplib listening on http://127.0.0.1:8000" << std::endl;
    Server.listen("localhost",8000);


    return 0;
}