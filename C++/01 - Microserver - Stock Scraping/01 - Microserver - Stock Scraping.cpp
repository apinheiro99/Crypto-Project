// 01 - Microserver - Stock Scraping.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"

static void
exit_nicely(PGconn* conn)
{
	PQfinish(conn);
	exit(1);
}

int main()
{
	const char* conninfo;
	PGconn* conn;
	PGresult* res;
	int	nFields, nRows;
	int i, j;

	/* Make a connection to the database */
	conninfo = "host=localhost port=5432 dbname=Crypto user=postgres password =Abc-1234";
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "%s", PQerrorMessage(conn));
		exit_nicely(conn);
	}



	res = PQexec(conn, "SELECT * FROM public.\"Resolution\" ORDER BY \"id_Resolution\" ASC ");

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}

	/* first, print out the attribute names */
	nFields = PQnfields(res);

	for (i = 0; i < nFields; i++)
		printf("%-15s", PQfname(res, i));
	printf("\n\n");

	/* next, print out the rows */
	nRows = PQntuples(res);

	for (i = 0; i < nRows; i++) {
		for (j = 0; j < nFields; j++)
			printf("%-15s", PQgetvalue(res, i, j));
		printf("\n");
	}

	PQclear(res);







	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
