php_output_handler_alias_register(const char *name, size_t name_len, php_output_handler_alias_ctor_t func TSRMLS_DC)
{
	if (!EG(current_module)) {
		zend_error(E_ERROR, "Cannot register an output handler alias outside of MINIT");
		return FAILURE;
	}
	return zend_hash_update(&php_output_handler_aliases, name, name_len+1, &func, sizeof(php_output_handler_alias_ctor_t *), NULL);
}
