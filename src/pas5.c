#include <stdio.h>
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include "deps/xgetopt/xgetopt.h"
#endif
#include <sqlite3.h>
#include "colors.h"

const char *PAS5_VERSION = "0.1.2"; // Major, Minor, Patch

int callback(void *, int, char **, char **);

int main(int argc, char *argv[])
{
	char opt = getopt(argc, argv, "v");
	while(opt != -1)
	{
		switch(opt)
		{
			case 'v':
				printf("pas5 version: %s\n", PAS5_VERSION);
				printf("by %s\n", "Alexander Popov");
				printf("%s\n", "GitHub: https://github.com/IIIypuk/pas5");
				return 0;

			default:
				break;
		}
	}

	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open("./pwd.db", &db);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	char user_input[999];
	printf("%s: ", "Enter URL");
	scanf("%s", user_input);
	char sql[999];
	sprintf(sql, "SELECT url, email, login, pass FROM passwords WHERE url LIKE '%%%s%%'", user_input);

	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Failed to select data.\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);

	return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	NotUsed = 0;

	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}
