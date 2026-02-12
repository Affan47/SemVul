static int lsqlite3_safe_rollback(sqlite3 *sqlite)
{
	char *errmsg;
	int ret;


	ret = sqlite3_exec(sqlite, "ROLLBACK;", NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		if (errmsg) {
			printf("lsqlite3_safe_rollback: Error: %s\n", errmsg);
			free(errmsg);
		}
		return -1;
	}

        return 0;
}
