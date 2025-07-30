

#include "database.h"



int init_database(void)
{
    conn = mysql_init(NULL);
    if(conn == NULL)
    {
        perror("db_init");
        return -1;
    }

    char *host = getenv("DB_HOST");
    char *user = getenv("DB_USER");
    char *pass = getenv("DB_PASS");
    char *db_name = getenv("DB_NAME");

    if(mysql_real_connect(conn, host, user, pass, db_name, 0, NULL, 0) == NULL)
    {
        perror("db_connect()");
        return -1;
    }

    return 0;

}


void close_conn(void)
{
    mysql_close(conn);
}



