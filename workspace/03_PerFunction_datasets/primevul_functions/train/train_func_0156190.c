static int _expand_arg(pam_handle_t *pamh, char **value)
{
  const char *orig=*value, *tmpptr=NULL;
  char *ptr;


  char type, tmpval[BUF_SIZE];


  char tmp[MAX_ENV];

  D(("Remember to initialize tmp!"));
  memset(tmp, 0, MAX_ENV);


  D(("Expanding <%s>",orig));
  while (*orig) {
    if ('\\' == *orig) {
      ++orig;
      if ('$' != *orig && '@' != *orig) {
	D(("Unrecognized escaped character: <%c> - ignoring", *orig));
	pam_syslog(pamh, LOG_ERR,
		   "Unrecognized escaped character: <%c> - ignoring",
		   *orig);
      } else if ((strlen(tmp) + 1) < MAX_ENV) {
	tmp[strlen(tmp)] = *orig++;
      } else {

	D(("Variable buffer overflow: <%s> + <%s>", tmp, tmpptr));
	pam_syslog (pamh, LOG_ERR, "Variable buffer overflow: <%s> + <%s>",
		 tmp, tmpptr);
	return PAM_BUF_ERR;
      }
      continue;
    }
    if ('$' == *orig || '@' == *orig) {
      if ('{' != *(orig+1)) {
	D(("Expandable variables must be wrapped in {}"
	   " <%s> - ignoring", orig));
	pam_syslog(pamh, LOG_ERR, "Expandable variables must be wrapped in {}"
		 " <%s> - ignoring", orig);
	if ((strlen(tmp) + 1) < MAX_ENV) {
	  tmp[strlen(tmp)] = *orig++;
	}
	continue;
      } else {
	D(("Expandable argument: <%s>", orig));
	type = *orig;
	orig+=2;
	ptr = strchr(orig, '}');
	if (ptr) {
	  *ptr++ = '\0';
	} else {
	  D(("Unterminated expandable variable: <%s>", orig-2));
	  pam_syslog(pamh, LOG_ERR,
		     "Unterminated expandable variable: <%s>", orig-2);
	  return PAM_ABORT;
	}
	strncpy(tmpval, orig, sizeof(tmpval));
	tmpval[sizeof(tmpval)-1] = '\0';
	orig=ptr;


	switch (type) {

	case '$':
	  D(("Expanding env var: <%s>",tmpval));
	  tmpptr = pam_getenv(pamh, tmpval);
	  D(("Expanded to <%s>", tmpptr));
	  break;

	case '@':
	  D(("Expanding pam item: <%s>",tmpval));
	  tmpptr = _pam_get_item_byname(pamh, tmpval);
	  D(("Expanded to <%s>", tmpptr));
	  break;

	default:
	  D(("Impossible error, type == <%c>", type));
	  pam_syslog(pamh, LOG_CRIT, "Impossible error, type == <%c>", type);
	  return PAM_ABORT;
	}

	if (tmpptr) {
	  if ((strlen(tmp) + strlen(tmpptr)) < MAX_ENV) {
	    strcat(tmp, tmpptr);
	  } else {

	    D(("Variable buffer overflow: <%s> + <%s>", tmp, tmpptr));
	    pam_syslog (pamh, LOG_ERR,
			"Variable buffer overflow: <%s> + <%s>", tmp, tmpptr);
	    return PAM_BUF_ERR;
	  }
	}
      }
    } else {
      if ((strlen(tmp) + 1) < MAX_ENV) {
	tmp[strlen(tmp)] = *orig++;
      } else {

	D(("Variable buffer overflow: <%s> + <%s>", tmp, tmpptr));
	pam_syslog(pamh, LOG_ERR,
		   "Variable buffer overflow: <%s> + <%s>", tmp, tmpptr);
	return PAM_BUF_ERR;
      }
    }
  }

  if (strlen(tmp) > strlen(*value)) {
    free(*value);
    if ((*value = malloc(strlen(tmp) +1)) == NULL) {
      D(("Couldn't malloc %d bytes for expanded var", strlen(tmp)+1));
      pam_syslog (pamh, LOG_ERR, "Couldn't malloc %lu bytes for expanded var",
	       (unsigned long)strlen(tmp)+1);
      return PAM_BUF_ERR;
    }
  }
  strcpy(*value, tmp);
  memset(tmp,'\0',sizeof(tmp));
  D(("Exit."));

  return PAM_SUCCESS;
}
