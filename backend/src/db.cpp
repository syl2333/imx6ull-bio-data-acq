#include "db.h"
#include "log.h"

char* errMsg = nullptr;
char errStr[128] = { 0 };
SQLiteWrapper::SQLiteWrapper(const std::string& db_name)
{
    open(db_name);
}

SQLiteWrapper::~SQLiteWrapper()
{

}

static int isExistCallback(void* table_exists, int argc, char** argv, char** azColName)
{
    *static_cast<bool*>(table_exists) = true;
    return 0;
}

bool SQLiteWrapper::init_tables()
{
    int ret;
    bool found = false;
    std::string isExistUsersPasswdTableSql = "\
        SELECT name FROM sqlite_master WHERE type='table' AND name='users_passwd';\
    ";
    
    ret = sqlite3_exec(m_db,isExistUsersPasswdTableSql.c_str(),isExistCallback,&found,&errMsg);
    if(ret != SQLITE_OK)
    {
        
        sprintf(errStr,"sql语句执行失败，位于%s:%d",__FILE__,__LINE__);
        Logger::getInstance().error(errStr);
    }
    if(found)
    {
        Logger::getInstance().info("在本地sqlite数据库中发现用户名-密码数据表！");
    }
    else
    {
        Logger::getInstance().info("在本地sqlite数据库中未发现用户名-密码数据表！");

        std::string createUsersPasswdTableSql = " \
            CREATE TABLE IF NOT EXISTS users_passwd ( \
                id INTEGER PRIMARY KEY AUTOINCREMENT,\
                name TEXT NOT NULL,\
                password TEXT NOT NULL\
            );\
        ";

    
        ret = sqlite3_exec(m_db,createUsersPasswdTableSql.c_str(),0,0,&errMsg);
        if(ret != SQLITE_OK)
        {
            Logger::getInstance().error("无法在本地sqlite数据库创建用户名-密码数据表！");
            Logger::getInstance().error(errMsg);
            return false;
        }
        
        Logger::getInstance().info("用户名-密码数据表创建成功");
    }

    std::string isExistSuperUserSql = "\
        SELECT * FROM users_passwd WHERE name = 'admin';\
    ";
    found = false;
    ret = sqlite3_exec(m_db,isExistSuperUserSql.c_str(),isExistCallback,&found,&errMsg);
    if(ret != SQLITE_OK)
    {
        sprintf(errStr,"sql语句执行失败，位于%s:%d",__FILE__,__LINE__);
        Logger::getInstance().error(errMsg);
        Logger::getInstance().error(errStr);
        return false;
    }
    if(found)
    {
        Logger::getInstance().info("在用户名-密码数据表中发现超级用户");
    }
    else
    {
        std::string insertSuperUserSql = "\
            INSERT INTO users_passwd (name, password) VALUES ('admin', 'adminadmin');\
        ";
        ret = sqlite3_exec(m_db,insertSuperUserSql.c_str(),0,0,&errMsg);

        if(ret != SQLITE_OK)
        {
            Logger::getInstance().error("无法在本地sqlite数据库创建超级用户！");
            Logger::getInstance().error(errMsg);
            return false;
        }
        
        Logger::getInstance().info("在本地sqlite数据库创建超级用户成功");
    }
    
    return true;
}

bool SQLiteWrapper::verifyUserPassword(std::string user, std::string passwd)
{
    std::string queried_passwd = query_password_by_name(user);
    if(passwd == queried_passwd)
        return true;
        
    return false;
}

bool SQLiteWrapper::open(const std::string &db_name)
{
    int ret = sqlite3_open(db_name.c_str(),&m_db);
    if(ret != SQLITE_OK)
    {
        //todo 使用log4cpp库记录
        Logger::getInstance().error("无法打开本地sqlite数据库！");
        return false;
    }
    
    Logger::getInstance().info("打开本地sqlite数据库");
    return true;
}

std::string SQLiteWrapper::query_password_by_name(const std::string &name)
{
    std::string password;
    std::string sql_query = "SELECT password FROM users_passwd WHERE name = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(m_db, sql_query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        Logger::getInstance().errorStream() << "无法准备查询语句: " << sqlite3_errmsg(m_db);
        return "";
    }

    // 绑定参数（防止SQL注入攻击）
    if (sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        Logger::getInstance().errorStream() << "无法绑定参数: " << sqlite3_errmsg(m_db);
        sqlite3_finalize(stmt);
        return "";
    }

    // 执行查询
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    } else if (rc != SQLITE_DONE) {
        Logger::getInstance().errorStream() << "查询执行错误: " << sqlite3_errmsg(m_db);
    }

    sqlite3_finalize(stmt);
    return password;
}
