#include "SqlLite.h"

void Sql::init() {
    sqlite3 *db1;
    SPI.begin();
    vfs_mount("/SD0", SS);
    sqlite3_initialize();
    int rc = sqlite3_open("/SD0/babyname.db", &this->dbLink);
    if (rc) {
        Serial.printf("Can't open database: %s\n",
                      sqlite3_errmsg(this->dbLink));
        return;
    }
}

void Sql::createTable() {
    sqlite3_stmt *res;
     const char *tail;

    String sql =
        "Select year, state, name, total_babies, primary_sex, primary_sex_ratio, \
                    per_100k_in_state from gendered_names \
                    where name between 'Bob' and 'Bobby'";
    int rc = sqlite3_prepare_v2(this->dbLink, sql.c_str(), 1000, &res, &tail);
    if (rc != SQLITE_OK) {
        //error
        Serial.println(sqlite3_errmsg(this->dbLink));
    }