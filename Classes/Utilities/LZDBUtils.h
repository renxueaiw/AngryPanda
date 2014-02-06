//
//  LZDBUtils.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-12.
//
//

#ifndef __AngryPanda__LZDBUtils__
#define __AngryPanda__LZDBUtils__

#include "cocos2d.h"
#include "sqlite3/sqlite3.h"

class LZDBUtils: public cocos2d::CCObject
{
private:
    LZDBUtils(void); // 单例
    
    sqlite3 *_db;
    std::string _sql;
    int _result;
   
public:
    static LZDBUtils* sharedDBUtils(void);
    virtual ~LZDBUtils(void);
    
    // 创建数据库
    void createSqlite3Database(const std::string filename);
    // 创建表
    bool createTable(const std::string sql);
    // 插入一条数据
    bool insertData(const std::string sql);
    // 更新一条数据
    bool updateData(const std::string sql);
    // 删除一条数据
    bool deleteData(const std::string sql);
    // 获取数据
    void queryData(const std::string sql, char ***result, int *row, int *col);
    // 关闭数据库
    void closeDatabase();
};

#endif /* defined(__AngryPanda__LZDBUtils__) */
