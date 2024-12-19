#include <stdio.h>
#include <libpq-fe.h>

int main()
{
    const char *conninfo = "host=localhost dbname=mydb user=myuser password=mypassword";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "connection failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);

        return 1;
    }

    printf("connected to the database successfully.\n");
    PQfinish(conn);

    return 0;
}
