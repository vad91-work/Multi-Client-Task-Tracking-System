
#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>


static MYSQL *conn;
static MYSQL_RES *res;
static MYSQL_ROW row; 

int init_database(void);
void close_conn(void);

#endif // DATABASE_H

