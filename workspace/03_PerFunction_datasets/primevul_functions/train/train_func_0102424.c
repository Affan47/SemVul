void php_filter_validate_mac(PHP_INPUT_FILTER_PARAM_DECL)
{
	char *input = Z_STRVAL_P(value);
	size_t input_len = Z_STRLEN_P(value);
	int tokens, length, i, offset, exp_separator_set;
	size_t exp_separator_len;
	char separator;
	char *exp_separator;
	zend_long ret = 0;
	zval *option_val;

	FETCH_STRING_OPTION(exp_separator, "separator");

	if (exp_separator_set && exp_separator_len != 1) {
		php_error_docref(NULL, E_WARNING, "Separator must be exactly one character long");
		RETURN_VALIDATION_FAILED;
	}

	if (14 == input_len) {


		tokens = 3;
		length = 4;
		separator = '.';
	} else if (17 == input_len && input[2] == '-') {

		tokens = 6;
		length = 2;
		separator = '-';
	} else if (17 == input_len && input[2] == ':') {

		tokens = 6;
		length = 2;
		separator = ':';
	} else {
		RETURN_VALIDATION_FAILED;
	}

	if (exp_separator_set && separator != exp_separator[0]) {
		RETURN_VALIDATION_FAILED;
	}


	for (i = 0; i < tokens; i++) {
		offset = i * (length + 1);

		if (i < tokens - 1 && input[offset + length] != separator) {

			RETURN_VALIDATION_FAILED
		}
		if (php_filter_parse_hex(input + offset, length, &ret) < 0) {

			RETURN_VALIDATION_FAILED
		}
	}
}
