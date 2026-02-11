php_filter_validate_regexp(PHP_INPUT_FILTER_PARAM_DECL)
{
	zval **option_val;
	char  *regexp;
	int regexp_len;
	long   option_flags;
	int    regexp_set, option_flags_set;

	pcre       *re = NULL;
	pcre_extra *pcre_extra = NULL;
	int preg_options = 0;

	int         ovector[3];
	int         matches;


	FETCH_STRING_OPTION(regexp, "regexp");
	FETCH_LONG_OPTION(option_flags, "flags");

	if (!regexp_set) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "'regexp' option missing");
		RETURN_VALIDATION_FAILED
	}

	re = pcre_get_compiled_regex(regexp, &pcre_extra, &preg_options TSRMLS_CC);
	if (!re) {
		RETURN_VALIDATION_FAILED
	}
	matches = pcre_exec(re, NULL, Z_STRVAL_P(value), Z_STRLEN_P(value), 0, 0, ovector, 3);


	if (matches < 0) {
		RETURN_VALIDATION_FAILED
	}
}
