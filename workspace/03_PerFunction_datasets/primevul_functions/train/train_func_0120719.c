void php_filter_magic_quotes(PHP_INPUT_FILTER_PARAM_DECL)
{
	zend_string *buf;


	buf = php_addslashes(Z_STR_P(value), 0);

	zval_ptr_dtor(value);
	ZVAL_STR(value, buf);
}
