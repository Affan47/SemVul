int sldns_fp2wire_rr_buf(FILE* in, uint8_t* rr, size_t* len, size_t* dname_len,
	struct sldns_file_parse_state* parse_state)
{
	char line[LDNS_RR_BUF_SIZE+1];
	ssize_t size;


	if((size = sldns_fget_token_l(in, line, LDNS_PARSE_SKIP_SPACE,
		LDNS_RR_BUF_SIZE, parse_state?&parse_state->lineno:NULL))
		== -1) {


		return LDNS_WIREPARSE_ERR_SYNTAX;
	}


	if(size == 0) {
		if(*len > 0)
			rr[0] = 0;
		*len = 0;
		*dname_len = 0;
		return LDNS_WIREPARSE_ERR_OK;
	}

	if(strncmp(line, "$ORIGIN", 7) == 0 && isspace((unsigned char)line[7])) {
		int s;
		strlcpy((char*)rr, line, *len);
		*len = 0;
		*dname_len = 0;
		if(!parse_state) return LDNS_WIREPARSE_ERR_OK;
		parse_state->origin_len = sizeof(parse_state->origin);
		s = sldns_str2wire_dname_buf(sldns_strip_ws(line+8),
			parse_state->origin, &parse_state->origin_len);
		if(s) parse_state->origin_len = 0;
		return s;
	} else if(strncmp(line, "$TTL", 4) == 0 && isspace((unsigned char)line[4])) {
		const char* end = NULL;
		strlcpy((char*)rr, line, *len);
		*len = 0;
		*dname_len = 0;
		if(!parse_state) return LDNS_WIREPARSE_ERR_OK;
		parse_state->default_ttl = sldns_str2period(
			sldns_strip_ws(line+5), &end);
	} else if (strncmp(line, "$INCLUDE", 8) == 0) {
		strlcpy((char*)rr, line, *len);
		*len = 0;
		*dname_len = 0;
		return LDNS_WIREPARSE_ERR_INCLUDE;
	} else if (strncmp(line, "$", 1) == 0) {
		strlcpy((char*)rr, line, *len);
		*len = 0;
		*dname_len = 0;
		return LDNS_WIREPARSE_ERR_INCLUDE;
	} else {
		int r = sldns_str2wire_rr_buf(line, rr, len, dname_len,
			parse_state?parse_state->default_ttl:0,
			(parse_state&&parse_state->origin_len)?
				parse_state->origin:NULL,
			parse_state?parse_state->origin_len:0,
			(parse_state&&parse_state->prev_rr_len)?
				parse_state->prev_rr:NULL,
			parse_state?parse_state->prev_rr_len:0);
		if(r == LDNS_WIREPARSE_ERR_OK && (*dname_len) != 0 &&
			parse_state &&
			(*dname_len) <= sizeof(parse_state->prev_rr)) {
			memmove(parse_state->prev_rr, rr, *dname_len);
			parse_state->prev_rr_len = (*dname_len);
		}
		return r;
	}
	return LDNS_WIREPARSE_ERR_OK;
}
