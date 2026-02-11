php_sqlite3_authorizer(void *autharg, int access_type, const char *arg3, const char *arg4, const char *arg5, const char *arg6)
{
	switch (access_type) {
		case SQLITE_ATTACH:
		{
			if (memcmp(arg3, ":memory:", sizeof(":memory:")) && *arg3) {
				TSRMLS_FETCH();

#if PHP_API_VERSION < 20100412
				if (PG(safe_mode) && (!php_checkuid(arg3, NULL, CHECKUID_CHECK_FILE_AND_DIR))) {
					return SQLITE_DENY;
				}
#endif

				if (php_check_open_basedir(arg3 TSRMLS_CC)) {
					return SQLITE_DENY;
				}
			}
			return SQLITE_OK;
		}

		default:

			return SQLITE_OK;
	}
}
