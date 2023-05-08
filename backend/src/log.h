#ifndef __LOG_H__
#define __LOG_H__

#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/PatternLayout.hh"

//使用设计模式中的单例模式，提供一个静态方法获取唯一的Logger类
//使用设计模式中的代理模式，让Logger类也具有log4cpp::Category类的一些接口
class Logger {
public:
    // 获取日志记录器实例的静态方法
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // 删除复制构造函数和赋值运算符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 记录日志的方法
    void info(const std::string& message) {
        __category.info(message);
    }

    void error(const std::string& message) {
        __category.error(message);
    }

    log4cpp::CategoryStream infoStream() {
        return __category.infoStream();
    }

    log4cpp::CategoryStream errorStream() {
        return __category.errorStream();
    }
private:
  // 私有构造函数
    Logger() {
        // 初始化log4cpp
        auto appender = new log4cpp::FileAppender("FileAppender","log.txt",false);
        auto patternLayout = new log4cpp::PatternLayout();
        patternLayout->setConversionPattern("%d [%t] %p: %m%n");
        appender->setLayout(patternLayout);

        __category.setAppender(appender);
        __category.setPriority(log4cpp::Priority::DEBUG);
    }

    // log4cpp的Category成员
    log4cpp::Category& __category = log4cpp::Category::getRoot();
};



#endif