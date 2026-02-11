php_userstreamop_closedir(php_stream *stream, int close_handle TSRMLS_DC)
{
	zval func_name;
	zval *retval = NULL;
	php_userstream_data_t *us = (php_userstream_data_t *)stream->abstract;

	assert(us != NULL);

	ZVAL_STRINGL(&func_name, USERSTREAM_DIR_CLOSE, sizeof(USERSTREAM_DIR_CLOSE)-1, 0);

	call_user_function_ex(NULL,
			&us->object,
			&func_name,
			&retval,
			0, NULL, 0, NULL TSRMLS_CC);

	if (retval)
		zval_ptr_dtor(&retval);

	zval_ptr_dtor(&us->object);

	efree(us);

	return 0;
}
