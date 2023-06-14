#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#include "../../build/1_sqlite/sqlite3.h"

int main() {
#define BUFSIZE 4096
    char input[BUFSIZE + 1];
    int len = read(0, input, BUFSIZE);
    input[len] = 0;

    sqlite3* db;

    sqlite3_open(":memory:", &db);
    const char* cur_stmt = input;
    const char* end = input + len;

    while (*cur_stmt) {
        sqlite3_stmt* stmt = NULL;
        const char* next_stmt = NULL;
        int rc;

        sqlite3_prepare_v2(db, cur_stmt, end - cur_stmt, &stmt, &next_stmt);

        if (cur_stmt == next_stmt) {
            sqlite3_finalize(stmt);
            break;
        }

        if (!stmt) {
            cur_stmt = next_stmt;
            continue;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
            ;
        sqlite3_finalize(stmt);

        cur_stmt = next_stmt;

        while (isspace((unsigned char)(*cur_stmt))) ++cur_stmt;
    }

    sqlite3_close(db);

    return 0;
}