#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../build/1_sqlite/sqlite3.h"

int main(int argc, char ** argv) {

    if (argc != 2) {
        printf("Usage: %s <inputfile>", argv[0]);
        exit(1);
    }

    sqlite3* db;

    sqlite3_open(argv[1], &db);
    sqlite3_close(db);

    return 0;
}