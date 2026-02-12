Decode mime header element in accordance with RFC 2047 and return array of objects containing 'charset' encoding and decoded 'text' */
PHP_FUNCTION(imap_mime_header_decode)
{

	zval myobject;
	zend_string *str;
	char *string, *charset, encoding, *text, *decode;
	zend_long charset_token, encoding_token, end_token, end, offset=0, i;
	unsigned long newlength;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &str) == FAILURE) {
		return;
	}

	array_init(return_value);

	string = ZSTR_VAL(str);
	end = ZSTR_LEN(str);

	charset = (char *) safe_emalloc((end + 1), 2, 0);
	text = &charset[end + 1];
	while (offset < end) {
		if ((charset_token = (zend_long)php_memnstr(&string[offset], "=?", 2, string + end))) {
			charset_token -= (zend_long)string;
			if (offset != charset_token) {

				memcpy(text, &string[offset], charset_token-offset);
				text[charset_token - offset] = 0x00;
				object_init(&myobject);
				add_property_string(&myobject, "charset", "default");
				add_property_string(&myobject, "text", text);
				zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &myobject);
			}
			if ((encoding_token = (zend_long)php_memnstr(&string[charset_token+2], "?", 1, string+end))) {
				encoding_token -= (zend_long)string;
				if ((end_token = (zend_long)php_memnstr(&string[encoding_token+3], "?=", 2, string+end))) {
					end_token -= (zend_long)string;
					memcpy(charset, &string[charset_token + 2], encoding_token - (charset_token + 2));
					charset[encoding_token-(charset_token + 2)] = 0x00;
					encoding=string[encoding_token + 1];
					memcpy(text, &string[encoding_token + 3], end_token - (encoding_token + 3));
					text[end_token - (encoding_token + 3)] = 0x00;
					decode = text;
					if (encoding == 'q' || encoding == 'Q') {
						for(i=0; text[i] != 0x00; i++) if (text[i] == '_') text[i] = ' ';
						decode = (char *)rfc822_qprint((unsigned char *) text, strlen(text), &newlength);
					} else if (encoding == 'b' || encoding == 'B') {
						decode = (char *)rfc822_base64((unsigned char *) text, strlen(text), &newlength);
					}
					if (decode == NULL) {
						efree(charset);
						zval_dtor(return_value);
						RETURN_FALSE;
					}
					object_init(&myobject);
					add_property_string(&myobject, "charset", charset);
					add_property_string(&myobject, "text", decode);
					zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &myobject);


					if (decode != text) {
						fs_give((void**)&decode);
					}

					offset = end_token+2;
					for (i = 0; (string[offset + i] == ' ') || (string[offset + i] == 0x0a) || (string[offset + i] == 0x0d) || (string[offset + i] == '\t'); i++);
					if ((string[offset + i] == '=') && (string[offset + i + 1] == '?') && (offset + i < end)) {
						offset += i;
					}
					continue;
				}
			}
		} else {


			charset_token = offset;
		}


		memcpy(text, &string[charset_token], end - charset_token);
		text[end - charset_token] = 0x00;
		object_init(&myobject);
		add_property_string(&myobject, "charset", "default");
		add_property_string(&myobject, "text", text);
		zend_hash_next_index_insert(Z_ARRVAL_P(return_value), &myobject);

		offset = end;
	}
	efree(charset);
}
