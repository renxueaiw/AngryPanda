//
//  LZDBUtils.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-12.
//
//

#include "LZDBUtils.h"

USING_NS_CC;

static LZDBUtils *m_sharedDBUtils = NULL;

LZDBUtils* LZDBUtils::sharedDBUtils()
{
    if (!m_sharedDBUtils) {
        m_sharedDBUtils = new LZDBUtils();
    }
    return m_sharedDBUtils;
}

LZDBUtils::LZDBUtils()
{
    _db = NULL;
}

LZDBUtils::~LZDBUtils()
{
}

// 创建数据库
void LZDBUtils::createSqlite3Database(const std::string filename)
{
    _db = NULL;
    // 指定数据库路径
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath()+filename;
//    std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(filename.c_str(), "");
    // 检测指定路径下的数据库是否存在 （这个检测有问题，路径里的空格没处理")
//    bool isExist = CCFileUtils::sharedFileUtils()->isFileExist(path.c_str());
//    if (!isExist) {
//        CCLog("%s不存在", path.c_str());
//    }
//    else {
//        CCLog("%s存在", path.c_str());
//    }
    
    CCLog("databae path: %s", path.c_str());
    _result = sqlite3_open(path.c_str(), &_db);
    if (_result == SQLITE_OK) {
        CCLog("open databse successed, _result = %d", _result);
    } else {
        CCLog("open databse failed, _result = %d", _result);
    }
}

// 创建表
bool LZDBUtils::createTable(const std::string sql)
{
    char *errmsg;
    _result = sqlite3_exec(_db, sql.c_str(), NULL, NULL, &errmsg);
    if (_result == SQLITE_OK) {
        CCLog("create table successed!, sql=%s",sql.c_str());
        return true;
    } else {
        CCLog("create table failed!, sql=%s, errmsg=%s",sql.c_str(), errmsg);
        return false;
    }
}

// 插入一条数据
bool LZDBUtils::insertData(const std::string sql)
{
    char *errmsg;
    _result = sqlite3_exec(_db, sql.c_str(), NULL, NULL, &errmsg);
    if (_result == SQLITE_OK) {
        CCLog(" insert data successed!, sql=%s",sql.c_str());
        return true;
    } else {
        CCLog(" insert data failed!, sql=%s \n errmsg=%s",sql.c_str(), errmsg);
        return false;
    }
}

// 更新一条数据
bool LZDBUtils::updateData(const std::string sql)
{
    _result = sqlite3_exec(_db, sql.c_str(), NULL, NULL, NULL);
    if (_result == SQLITE_OK) {
        CCLog(" update data successed!, sql=%s",sql.c_str());
        return true;
    } else {
        CCLog(" update data failed!, sql=%s",sql.c_str());
        return false;
    }
}

// 删除数据
bool LZDBUtils::deleteData(const std::string sql)
{
    _result = sqlite3_exec(_db, sql.c_str(), NULL, NULL, NULL);
    if (_result == SQLITE_OK) {
        CCLog(" delete data successed!, sql=%s",sql.c_str());
        return true;
    } else {
        CCLog(" delete data failed!, sql=%s",sql.c_str());
        return false;
    }
}

// 查询数据
void LZDBUtils::queryData(const std::string sql, char ***result, int *row, int *col)
{
    _result = sqlite3_get_table(_db, sql.c_str(), result, row, col, NULL);
    if (_result == SQLITE_OK) {
        CCLog(" query data successed!, sql=%s",sql.c_str());
    } else {
        CCLog(" query data failed!, sql=%s",sql.c_str());
    }
}

// 关闭数据库
void LZDBUtils::closeDatabase()
{
    sqlite3_close(_db);
//    CC_SAFE_DELETE(_db);
}
