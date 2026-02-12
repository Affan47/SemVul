int ldb_msg_append_steal_string(struct ldb_message *msg,
				const char *attr_name, char *str,
				int flags)
{
	struct ldb_val val;

	val.data = (uint8_t *)str;
	val.length = strlen(str);

	if (val.length == 0) {

		return LDB_SUCCESS;
	}

	return ldb_msg_append_steal_value(msg, attr_name, &val, flags);
}
