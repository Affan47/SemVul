static void ldb_tevent_debug(void *context, enum tevent_debug_level level,
			     const char *fmt, va_list ap)
{
	struct ldb_context *ldb = talloc_get_type(context, struct ldb_context);
	enum ldb_debug_level ldb_level = LDB_DEBUG_FATAL;

	switch (level) {
	case TEVENT_DEBUG_FATAL:
		ldb_level = LDB_DEBUG_FATAL;
		break;
	case TEVENT_DEBUG_ERROR:
		ldb_level = LDB_DEBUG_ERROR;
		break;
	case TEVENT_DEBUG_WARNING:
		ldb_level = LDB_DEBUG_WARNING;
		break;
	case TEVENT_DEBUG_TRACE:
		ldb_level = LDB_DEBUG_TRACE;
		break;
	};


	ldb_vdebug(ldb, ldb_level, fmt, ap);
}
