static int php_libxml_post_deactivate()
{
	TSRMLS_FETCH();

	xmlSetGenericErrorFunc(NULL, NULL);
	xmlSetStructuredErrorFunc(NULL, NULL);

	xmlParserInputBufferCreateFilenameDefault(NULL);
	xmlOutputBufferCreateFilenameDefault(NULL);

	if (LIBXML(stream_context)) {

		efree(LIBXML(stream_context));
		LIBXML(stream_context) = NULL;
	}
	smart_str_free(&LIBXML(error_buffer));
	if (LIBXML(error_list)) {
		zend_llist_destroy(LIBXML(error_list));
		efree(LIBXML(error_list));
		LIBXML(error_list) = NULL;
	}
	xmlResetLastError();

	return SUCCESS;
}
