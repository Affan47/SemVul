wi_array_init_with_argument_string(wi_array_t *array, wi_string_t *string, wi_integer_t index) {
	wi_string_t		*data;
	const char		*cstring;
	char			*buffer, *end;
	wi_uinteger_t	count;
	wi_boolean_t	squote, dquote, bsquote;

	array		= wi_array_init_with_capacity(array, 0);
	cstring		= wi_string_cstring(string);
	buffer		= wi_malloc(strlen(cstring) + 1);
	count		= 0;

	squote = dquote = bsquote = false;

	while(*cstring) {
		if(index < 0 || (index >= 0 && count != (wi_uinteger_t) index)) {
			while(isspace(*cstring))
				cstring++;
		}

		end = buffer;

		while(*cstring) {
			if(index >= 0 && count == (wi_uinteger_t) index) {
				*end++ = *cstring++;

				continue;
			}

			if(isspace(*cstring) && !squote && !dquote && !bsquote)
				break;

			if(bsquote) {
				bsquote = false;
				*end++ = *cstring;
			}
			else if(squote) {
				if(*cstring == '\'')
					squote = false;
				else
					*end++ = *cstring;
			}
			else if(dquote) {
				if(*cstring == '"')
					dquote = false;
				else
					*end++ = *cstring;
			}
			else {
				if(*cstring == '\'')
					squote = true;
				else if(*cstring == '"')
					dquote = true;
				else if(*cstring == '\\')
					bsquote = true;
				else
					*end++ = *cstring;
			}

			cstring++;
		}

		*end = '\0';

		data = wi_string_init_with_cstring(wi_string_alloc(), buffer);
		_wi_array_add_data(array, data);
		wi_release(data);

		count++;

		while(isspace(*cstring))
			cstring++;
	}

	wi_free(buffer);

	return array;
}
