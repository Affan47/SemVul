static PHP_FUNCTION(session_register_shutdown)
{
	php_shutdown_function_entry shutdown_function_entry;


	shutdown_function_entry.arg_count = 1;
	shutdown_function_entry.arguments = (zval *) safe_emalloc(sizeof(zval), 1, 0);

	ZVAL_STRING(&shutdown_function_entry.arguments[0], "session_write_close");

	if (!append_user_shutdown_function(shutdown_function_entry)) {
		zval_ptr_dtor(&shutdown_function_entry.arguments[0]);
		efree(shutdown_function_entry.arguments);


		php_session_flush(1);
		php_error_docref(NULL, E_WARNING, "Unable to register session flush function");
	}
}
