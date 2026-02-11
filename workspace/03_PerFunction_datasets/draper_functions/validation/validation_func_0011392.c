wi_string_index_of_string_in_range(wi_string_t *string, wi_string_t *otherstring, wi_uinteger_t options, wi_range_t range) {
	char			*p;
	wi_uinteger_t	i, index;
	wi_boolean_t	insensitive = false;

	_WI_STRING_RANGE_ASSERT(string, range);

	if(range.length == 0)
		return WI_NOT_FOUND;

	if(options & WI_STRING_CASE_INSENSITIVE) {
		insensitive = true;
	}
	else if(options & WI_STRING_SMART_CASE_INSENSITIVE) {
		insensitive = true;

		for(i = 0; i < otherstring->length; i++) {
			if(isupper(otherstring->string[i])) {
				insensitive = false;

				break;
			}
		}
	}

	if(options & WI_STRING_BACKWARDS) {
		if(insensitive)
			p = wi_strrncasestr(string->string + range.location, otherstring->string, range.length);
		else
			p = wi_strrnstr(string->string + range.location, otherstring->string, range.length);
	} else {
		if(insensitive)
			p = wi_strncasestr(string->string + range.location, otherstring->string, range.length);
		else
			p = wi_strnstr(string->string + range.location, otherstring->string, range.length);
	}

	if(!p)
		return WI_NOT_FOUND;

	index = p - string->string;

	if(index > range.location + range.length)
		return WI_NOT_FOUND;

	return index;
}
