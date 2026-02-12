drill_file_p(gerb_file_t *fd, gboolean *returnFoundBinary)
{
    char *buf=NULL, *tbuf;
    int len = 0;
    char *letter;
    int ascii;
    int zero = 48;
    int nine = 57;
    int i;
    gboolean found_binary = FALSE;
    gboolean found_M48 = FALSE;
    gboolean found_M30 = FALSE;
    gboolean found_percent = FALSE;
    gboolean found_T = FALSE;
    gboolean found_X = FALSE;
    gboolean found_Y = FALSE;
    gboolean end_comments=FALSE;

    tbuf = g_malloc(MAXL);
    if (tbuf == NULL)
	GERB_FATAL_ERROR(
		"malloc buf failed while checking for drill file in %s()",
		__FUNCTION__);

    while (fgets(tbuf, MAXL, fd->fd) != NULL) {
	len = strlen(tbuf);
	buf = tbuf;

	if(!end_comments){
		if(g_strstr_len(buf, len, ";")!=NULL){
			for (i = 0; i < len-1; ++i) {
				if (buf[i] == '\n'
				&&  buf[i+1] != ';'
				&&  buf[i+1] != '\r'
				&&  buf[i+1] != '\n') {
					end_comments = TRUE;


					buf = &tbuf[i+1];

				}
			}
			if(!end_comments)
				continue;
		}
		else
			end_comments=TRUE;
	}


	len = strlen(buf);

	for (i = 0; i < len; i++) {
	    ascii = (int) buf[i];
	    if ((ascii > 128) || (ascii < 0)) {
		found_binary = TRUE;
	    }
	}


	if (g_strstr_len(buf, len, "M48")) {
	    found_M48 = TRUE;
	}


	if (g_strstr_len(buf, len, "M30")) {
	    if (found_percent) {
		found_M30 = TRUE;
	    }
	}


	if ((letter = g_strstr_len(buf, len, "%")) != NULL) {
	    if ((letter[1] ==  '\r') || (letter[1] ==  '\n'))
		found_percent = TRUE;
	}


	if ((letter = g_strstr_len(buf, len, "T")) != NULL) {
	    if (!found_T && (found_X || found_Y)) {
		found_T = FALSE;
	    } else {
		if (isdigit( (int) letter[1])) {
		    found_T = TRUE;
		}
	    }
	}


	if ((letter = g_strstr_len(buf, len, "X")) != NULL) {
	    ascii = (int) letter[1];
	    if ((ascii >= zero) && (ascii <= nine)) {
		found_X = TRUE;
	    }
	}
	if ((letter = g_strstr_len(buf, len, "Y")) != NULL) {
	    ascii = (int) letter[1];
	    if ((ascii >= zero) && (ascii <= nine)) {
		found_Y = TRUE;
	    }
	}
    }

    rewind(fd->fd);
    g_free(tbuf);
    *returnFoundBinary = found_binary;


    if ( ((found_X || found_Y) && found_T) &&
	 (found_M48 || (found_percent && found_M30)) )
	return TRUE;
    else if (found_M48 && found_T && found_percent && found_M30)


	return TRUE;
    else
	return FALSE;
}
