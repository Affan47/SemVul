db_upgrade_reinsert(void *arg, int argc, char *argv[], char *column_names[])
{
	struct sqlite3 *db = static_cast < struct sqlite3 *>(arg);
	bool mls = (argc == 7);
	assert(argc >= 6 && argc <= 7);
	uint32_t obj_class = static_cast < uint32_t > (atoi(argv[(mls ? 5 : 4)]));

	switch (obj_class)
	{
	case 16:
		obj_class = QPOL_CLASS_BLK_FILE;
		break;
	case 8:
		obj_class = QPOL_CLASS_CHR_FILE;
		break;
	case 2:
		obj_class = QPOL_CLASS_DIR;
		break;
	case 64:
		obj_class = QPOL_CLASS_FIFO_FILE;
		break;
	case 1:
		obj_class = QPOL_CLASS_FILE;
		break;
	case 4:
		obj_class = QPOL_CLASS_LNK_FILE;
		break;
	case 32:
		obj_class = QPOL_CLASS_SOCK_FILE;
		break;
	}

	char *insert_stmt = NULL;
	if (mls)
	{
		if (asprintf(&insert_stmt,
			     "INSERT INTO new_paths (path, ino, dev, user, role, type, range, obj_class, symlink_target) VALUES ('%s', %s, 0, %s, 0, %s, %s, %u, '%s')",
			     argv[0], argv[1], argv[2], argv[3], argv[4], obj_class, argv[6]) < 0)
		{
			return -1;
		}
	}
	else
	{
		if (asprintf(&insert_stmt,
			     "INSERT INTO new_paths (path, ino, dev, user, role, type, range, obj_class, symlink_target) VALUES ('%s', %s, 0, %s, 0, %s, 0, %u, '%s')",
			     argv[0], argv[1], argv[2], argv[3], obj_class, argv[5]) < 0)
		{
			return -1;
		}
	}
	if (sqlite3_exec(db, insert_stmt, NULL, NULL, NULL) != SQLITE_OK)
	{
		free(insert_stmt);
		return -1;
	}
	free(insert_stmt);
	return 0;
}
