

#include "database.h"


//init database
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

//close db connection
void close_conn(void)
{
    mysql_close(conn);
}

int register_user_db(char *username, char password)
{

    
    char insert_final_query[200];

    char escape_user[128], escape_pass[128];

    mysql_real_escape_string(conn, escape_user, username, strlen(username));
    mysql_real_escape_string(conn, escape_pass, password, strlen(password));

    sprintf(insert_final_query, "INSERT INTO users(username, password) VALUES ('%s', '%s')", username, password);

    int rs = mysql_query(conn, insert_final_query);

    if(rs)
    {
        fprintf(stderr, "Insert failed: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
