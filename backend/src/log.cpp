#include "log.h"

log4cpp::Category &category = log4cpp::Category::getInstance("backend_log");

void log4cpp_init()
{
    log4cpp::Appender *appender = new log4cpp::FileAppender("FileAppender","log.txt",false);

        // 创建一个 PatternLayout，并设置输出格式
    log4cpp::PatternLayout *layout = new log4cpp::PatternLayout();
    layout->setConversionPattern("%d: [%p] %m%n");

    // 将 PatternLayout 应用到 FileAppender
    appender->setLayout(layout);

    // 获取一个名为 "example" 的 Category 实例，并设置优先级
    
    category.setAppender(appender);
    category.setPriority(log4cpp::Priority::DEBUG);

    // 输出不同级别的日志
    // category.debug("Debug message");
    // category.info("Info message");
    // category.notice("Notice message");
    // category.warn("Warning message");
    // category.error("Error message");
    // category.fatal("Fatal message");

    // 关闭 log4cpp，清理资源
    //log4cpp::Category::shutdown();
}
