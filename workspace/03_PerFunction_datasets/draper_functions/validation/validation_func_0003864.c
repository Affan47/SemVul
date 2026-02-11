amule_version(PHP_VALUE_NODE *val)
{
	if ( !val ) {
		return;
	}
	value_value_free(val);

	val->type = PHP_VAL_STRING;
	val->str_val = strdup(PACKAGE_VERSION);
}
