int ldb_msg_append_string(struct ldb_message *msg,
			  const char *attr_name, const char *str, int flags)
{
	struct ldb_val val;

	val.data = discard_const_p(uint8_t, str);
	val.length = strlen(str);

	if (val.length == 0) {

		return LDB_SUCCESS;
	}

	return ldb_msg_append_value(msg, attr_name, &val, flags);
}
