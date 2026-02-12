Close an IMAP stream */
PHP_FUNCTION(imap_close)
{
	zval *streamind;
	pils *imap_le_struct=NULL;
	zend_long options = 0, flags = NIL;
	int argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(argc, "r|l", &streamind, &options) == FAILURE) {
		return;
	}

	if ((imap_le_struct = (pils *)zend_fetch_resource(Z_RES_P(streamind), "imap", le_imap)) == NULL) {
		RETURN_FALSE;
	}

	if (argc == 2) {
		flags = options;


		if (flags && ((flags & ~PHP_EXPUNGE) != 0)) {
			php_error_docref(NULL, E_WARNING, "invalid value for the flags parameter");
			RETURN_FALSE;
		}


		if (flags & PHP_EXPUNGE) {
			flags ^= PHP_EXPUNGE;
			flags |= CL_EXPUNGE;
		}
		imap_le_struct->flags = flags;
	}

	zend_list_close(Z_RES_P(streamind));

	RETURN_TRUE;
}
