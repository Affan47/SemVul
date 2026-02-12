ldns_str2rdf_dname(ldns_rdf **d, const char *str)
{
	size_t len;

	const char *s;
	uint8_t *q, *pq, label_len;
	uint8_t buf[LDNS_MAX_DOMAINLEN + 1];
	*d = NULL;

	len = strlen((char*)str);

	if (len > LDNS_MAX_DOMAINLEN * 4) {
		return LDNS_STATUS_DOMAINNAME_OVERFLOW;
	}
	if (0 == len) {
		return LDNS_STATUS_DOMAINNAME_UNDERFLOW;
	}


	if (1 == len && *str == '.') {
		*d = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME, 1, "\0");
		return LDNS_STATUS_OK;
	}


	len = 0;
	q = buf+1;
	pq = buf;
	label_len = 0;
	for (s = str; *s; s++, q++) {
		if (q > buf + LDNS_MAX_DOMAINLEN) {
			return LDNS_STATUS_DOMAINNAME_OVERFLOW;
		}
		*q = 0;
		switch (*s) {
		case '.':
			if (label_len > LDNS_MAX_LABELLEN) {
				return LDNS_STATUS_LABEL_OVERFLOW;
			}
			if (label_len == 0) {
				return LDNS_STATUS_EMPTY_LABEL;
			}
			len += label_len + 1;
			*pq = label_len;
			label_len = 0;
			pq = q;
			break;
		case '\\':

			s += 1;
			if (! parse_escape(q, &s)) {
				return LDNS_STATUS_SYNTAX_BAD_ESCAPE;
			}
			s -= 1;
			label_len++;
			break;
		default:
			*q = (uint8_t)*s;
			label_len++;
		}
	}


	if (!ldns_dname_str_absolute(str)) {
		if (q > buf + LDNS_MAX_DOMAINLEN) {
			return LDNS_STATUS_DOMAINNAME_OVERFLOW;
		}
                if (label_len > LDNS_MAX_LABELLEN) {
                        return LDNS_STATUS_LABEL_OVERFLOW;
                }
                if (label_len == 0) {
                        return LDNS_STATUS_EMPTY_LABEL;
                }
		len += label_len + 1;
		*pq = label_len;
		*q = 0;
	}
	len++;

	*d = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME, len, buf);
	return LDNS_STATUS_OK;
}
