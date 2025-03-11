#include <stdio.h>
#include "include/sqlite3.h"

int init_database(){
    sqlite3 *db;
    int return_code;
    char *err_msg = NULL;

    return_code = sqlite3_open("urlshortner.db",&db);

    if(return_code != SQLITE_OK){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS urls ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "original_url TEXT NOT NULL,"
        "short_code TEXT NOT NULL UNIQUE,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    return_code = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if(return_code!= SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main(){
    init_database;
    return 0;
}