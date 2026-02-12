static int initialize(struct lsqlite3_private *lsqlite3,
		      struct ldb_context *ldb, const char *url,
		      unsigned int flags)
{
	TALLOC_CTX *local_ctx;
        long long queryInt;
	int rollback = 0;
	char *errmsg;
        char *schema;
        int ret;


	local_ctx = talloc_named(lsqlite3, 0, "lsqlite3_rename local context");
	if (local_ctx == NULL) {
		return -1;
	}

	schema = lsqlite3_tprintf(local_ctx,


                "CREATE TABLE ldb_info AS "
                "  SELECT 'LDB' AS database_type,"
                "         '1.0' AS version;"


                "CREATE TABLE ldb_entry "
                "("
                "  eid     INTEGER PRIMARY KEY AUTOINCREMENT,"
                "  dn      TEXT UNIQUE NOT NULL,"
		"  norm_dn TEXT UNIQUE NOT NULL"
                ");"


                "CREATE TABLE ldb_object_classes"
                "("
                "  class_name            TEXT PRIMARY KEY,"
                "  parent_class_name     TEXT,"
                "  tree_key              TEXT UNIQUE,"
                "  max_child_num         INTEGER DEFAULT 0"
                ");"


                "CREATE TABLE ldb_attribute_values"
                "("
                "  eid             INTEGER REFERENCES ldb_entry,"
                "  attr_name       TEXT,"
                "  norm_attr_name  TEXT,"
                "  attr_value      TEXT,"
                "  norm_attr_value TEXT "
                ");"


                "CREATE INDEX ldb_attribute_values_eid_idx "
                "  ON ldb_attribute_values (eid);"

                "CREATE INDEX ldb_attribute_values_name_value_idx "
                "  ON ldb_attribute_values (attr_name, norm_attr_value);"


                "CREATE TRIGGER ldb_object_classes_insert_tr"
                "  AFTER INSERT"
                "  ON ldb_object_classes"
                "  FOR EACH ROW"
                "    BEGIN"
                "      UPDATE ldb_object_classes"
                "        SET tree_key = COALESCE(tree_key, "
                "              ("
                "                SELECT tree_key || "
                "                       (SELECT base160(max_child_num + 1)"
                "                                FROM ldb_object_classes"
                "                                WHERE class_name = "
                "                                      new.parent_class_name)"
                "                  FROM ldb_object_classes "
                "                  WHERE class_name = new.parent_class_name "
                "              ));"
                "      UPDATE ldb_object_classes "
                "        SET max_child_num = max_child_num + 1"
                "        WHERE class_name = new.parent_class_name;"
                "    END;"


                "INSERT INTO ldb_object_classes "
                "    (class_name, tree_key) "
                "  VALUES "
                "    ('TOP', '0001');");


        if (strncmp(url, "sqlite3://", 10) != 0) {
                return SQLITE_MISUSE;
        }


        url += 10;


        if ((ret = sqlite3_open(url, &lsqlite3->sqlite)) != SQLITE_OK) {
                return ret;
        }


	ret = sqlite3_exec(lsqlite3->sqlite, "PRAGMA auto_vacuum = 1;", NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		if (errmsg) {
			printf("lsqlite3 initializaion error: %s\n", errmsg);
			free(errmsg);
		}
		goto failed;
	}

	if (flags & LDB_FLG_NOSYNC) {

		ret = sqlite3_exec(lsqlite3->sqlite, "PRAGMA synchronous = OFF;", NULL, NULL, &errmsg);
		if (ret != SQLITE_OK) {
			if (errmsg) {
				printf("lsqlite3 initializaion error: %s\n", errmsg);
				free(errmsg);
			}
			goto failed;
		}
	}


        if ((ret = sqlite3_busy_timeout(lsqlite3->sqlite,
                                        30000)) != SQLITE_OK) {
                return ret;
        }


        if ((ret =
             sqlite3_create_function(lsqlite3->sqlite,
                                     "base160_next",
                                     1,
                                     SQLITE_ANY,
                                     NULL,
                                     base160next_sql,
                                     NULL,
                                     NULL
                     )) != SQLITE_OK) {
                return ret;
        }


        if ((ret =
             sqlite3_create_function(lsqlite3->sqlite,
                                     "base160",
                                     1,
                                     SQLITE_ANY,
                                     NULL,
                                     base160_sql,
                                     NULL,
                                     NULL
                     )) != SQLITE_OK) {
                return ret;
        }


        if ((ret =
             sqlite3_create_function(lsqlite3->sqlite,
                                     "ldap_compare",
                                     4,
                                     SQLITE_ANY,
                                     ldb  ,
                                     lsqlite3_compare,
                                     NULL,
                                     NULL
                     )) != SQLITE_OK) {
                return ret;
        }


	ret = sqlite3_exec(lsqlite3->sqlite, "BEGIN EXCLUSIVE;", NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		if (errmsg) {
			printf("lsqlite3: initialization error: %s\n", errmsg);
			free(errmsg);
		}
		goto failed;
	}
	rollback = 1;


        if (query_int(lsqlite3,
                      &queryInt,
                      "SELECT COUNT(*)\n"
                      "  FROM sqlite_master\n"
                      "  WHERE type = 'table';") != 0) {
		goto failed;
        }

        if (queryInt == 0) {


		ret = sqlite3_exec(lsqlite3->sqlite, schema, NULL, NULL, &errmsg);
		if (ret != SQLITE_OK) {
			if (errmsg) {
				printf("lsqlite3 initializaion error: %s\n", errmsg);
				free(errmsg);
			}
			goto failed;
		}
        } else {


                if (query_int(lsqlite3,
                              &queryInt,
                              "SELECT "
                              "  (SELECT COUNT(*) = 2"
                              "     FROM sqlite_master "
                              "     WHERE type = 'table' "
                              "       AND name IN "
                              "         ("
                              "           'ldb_entry', "
                              "           'ldb_object_classes' "
                              "         ) "
                              "  ) "
                              "  AND "
                              "  (SELECT 1 "
                              "     FROM ldb_info "
                              "     WHERE database_type = 'LDB' "
                              "       AND version = '1.0'"
                              "  );") != 0 ||
                    queryInt != 1) {


			goto failed;
                }
        }


	ret = sqlite3_exec(lsqlite3->sqlite, "COMMIT;", NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		if (errmsg) {
			printf("lsqlite3: iniialization error: %s\n", errmsg);
			free(errmsg);
		}
		goto failed;
	}

        return SQLITE_OK;

failed:
	if (rollback) lsqlite3_safe_rollback(lsqlite3->sqlite);
	sqlite3_close(lsqlite3->sqlite);
	return -1;
}
