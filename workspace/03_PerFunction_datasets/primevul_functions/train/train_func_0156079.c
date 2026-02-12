Parse a set of mail headers contained in a string, and return an object similar to imap_headerinfo() */
PHP_FUNCTION(imap_rfc822_parse_headers)
{
	zend_string *headers, *defaulthost = NULL;
	ENVELOPE *en;
	int argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(argc, "S|S", &headers, &defaulthost) == FAILURE) {
		return;
	}

	if (argc == 2) {
		rfc822_parse_msg(&en, NULL, ZSTR_VAL(headers), ZSTR_LEN(headers), NULL, ZSTR_VAL(defaulthost), NIL);
	} else {
		rfc822_parse_msg(&en, NULL, ZSTR_VAL(headers), ZSTR_LEN(headers), NULL, "UNKNOWN", NIL);
	}


	_php_make_header_object(return_value, en);
	mail_free_envelope(&en);
}
