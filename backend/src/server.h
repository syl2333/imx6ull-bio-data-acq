#ifndef __SERVER_H__
#define __SERVER_H__

#include "httplib.h"


//使用设计模式中的Facade（外观）模式
class HttpHandlerFacade {
public:
  void initHandlers(httplib::Server& server) {
    server.Post("/login", handleLogin);
    server.Get("/data", handleDataRequest);
    // 其他HTTP请求处理函数
  }

private:
  static void handleLogin(const httplib::Request& req, httplib::Response& res) {
    // 处理登录请求的实现
  }

  static void handleDataRequest(const httplib::Request& req, httplib::Response& res) {
    // 处理数据请求的实现
  }

  // 其他请求处理函数
};

#endif