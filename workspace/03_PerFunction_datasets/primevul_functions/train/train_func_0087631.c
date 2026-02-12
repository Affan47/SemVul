static int ac_match_handler(AC_MATCH_t *m, AC_TEXT_t *txt, AC_REP_t *match) {
  int min_len = (txt->length < m->patterns->length) ? txt->length : m->patterns->length;
  char buf[64] = {'\0'}, *whatfound;
  int min_buf_len = (txt->length > 63 ) ? 63 : txt->length;
  u_int buf_len = strlen(buf);

  strncpy(buf, txt->astring, min_buf_len);
  buf[min_buf_len] = '\0';

#ifdef MATCH_DEBUG
  printf("Searching [to search: %s/%u][pattern: %s/%u] [len: %d][match_num: %u][%s]\n", buf,
	 (unigned int) txt->length, m->patterns->astring, (unigned int) m->patterns->length, min_len, m->match_num,
	 m->patterns->astring);
#endif

  whatfound = strstr(buf, m->patterns->astring);

#ifdef MATCH_DEBUG
  printf("[NDPI] %s() [searching=%s][pattern=%s][%s][%c]\n", __FUNCTION__, buf, m->patterns->astring,
	 whatfound ? whatfound : "<NULL>", whatfound[-1]);
#endif

  if(whatfound) {


    if((whatfound != buf) && (m->patterns->astring[0] != '.')
       && strchr(m->patterns->astring, '.') ) {
      int len = strlen(m->patterns->astring);

      if((whatfound[-1] != '.') || ((m->patterns->astring[len - 1] != '.') &&
				    (whatfound[len] != '\0') )) {
	return(0);
      } else {
	memcpy(match, &m->patterns[0].rep, sizeof(AC_REP_t));
	return(0);
      }
    }
  }


  memcpy(match, &m->patterns[0].rep, sizeof(AC_REP_t));

  if(((buf_len >= min_len) && (strncmp(&buf[buf_len - min_len], m->patterns->astring, min_len) == 0)) ||
     (strncmp(buf, m->patterns->astring, min_len) == 0)
     ) {
#ifdef MATCH_DEBUG
    printf("Found match [%s][%s] [len: %d]"

	   "\n",
	   buf, m->patterns->astring, min_len );
#endif
    return(1);
  } else {
#ifdef MATCH_DEBUG
    printf("NO match found: continue\n");
#endif
    return(0);
  }
}
