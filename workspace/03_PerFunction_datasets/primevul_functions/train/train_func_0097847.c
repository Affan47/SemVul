static char *sql_create_statement(const char *statement, const char *prop,
				  const char *user, const char *realm,
				  const char *value,
				  const sasl_utils_t *utils)
{
    const char *ptr, *line_ptr;
    char *buf, *buf_ptr;
    int filtersize;
    int ulen, plen, rlen, vlen;
    int numpercents=0;
    int biggest;
    size_t i;


    ulen = (int)strlen(user);
    rlen = (int)strlen(realm);
    plen = (int)strlen(prop);
    vlen = (int)sql_len(value);


    for (i = 0; i < strlen(statement); i++) {
	if (statement[i] == '%') {
	    numpercents++;
	}
    }


    biggest = sql_max(sql_max(ulen, rlen), sql_max(plen, vlen));


    filtersize = (int)strlen(statement) + 1 + (numpercents*biggest)+1;


    buf = (char *) utils->malloc(filtersize);

    if (!buf) {
	MEMERROR(utils);
	return NULL;
    }

    buf_ptr = buf;
    line_ptr = statement;


    while ( (ptr = strchr(line_ptr, '%')) ) {

	memcpy(buf_ptr, line_ptr, ptr - line_ptr);
	buf_ptr += ptr - line_ptr;
	ptr++;
	switch (ptr[0]) {
	case '%':
	    buf_ptr[0] = '%';
	    buf_ptr++;
	    break;
	case 'u':
	    memcpy(buf_ptr, user, ulen);
	    buf_ptr += ulen;
	    break;
	case 'r':
	    memcpy(buf_ptr, realm, rlen);
	    buf_ptr += rlen;
	    break;
	case 'p':
	    memcpy(buf_ptr, prop, plen);
	    buf_ptr += plen;
	    break;
	case 'v':
	    if (value != NULL) {
		memcpy(buf_ptr, value, vlen);
		buf_ptr += vlen;
	    }
	    else {
		utils->log(utils->conn, SASL_LOG_ERR,
			   "'%%v' shouldn't be in a SELECT or DELETE");
	    }
	    break;
	default:
	    buf_ptr[0] = '%';
	    buf_ptr[1] = ptr[0];
	    buf_ptr += 2;
	    break;
	}
	ptr++;
	line_ptr = ptr;
    }

    memcpy(buf_ptr, line_ptr, strlen(line_ptr)+1);

    if (buf_ptr[strlen(buf_ptr-1)] != ';') {
	strcat(buf_ptr, ";");
    }

    return (buf);
}
