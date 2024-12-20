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

    PGresult *res = PQexec(conn, "SELECT version();");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);

        return 1;
    }

    printf("PostgreSQL version: %s\n", PQgetvalue(res, 0, 0));
    PQclear(res);
    PQfinish(conn);

    return 0;
}
