_parse_line (const pam_handle_t *pamh, char *buffer, VAR *var)
{


  int length, quoteflg=0;
  char *ptr, **valptr, *tmpptr;

  D(("Called buffer = <%s>", buffer));

  length = strcspn(buffer," \t\n");

  if ((var->name = malloc(length + 1)) == NULL) {
    pam_syslog(pamh, LOG_ERR, "Couldn't malloc %d bytes", length+1);
    return PAM_BUF_ERR;
  }


  strncpy(var->name, buffer, length);
  var->name[length] = '\0';
  D(("var->name = <%s>, length = %d", var->name, length));


  ptr = buffer+length;
  while ((length = strspn(ptr, " \t")) > 0) {
    ptr += length;
    D((ptr));
    if (strncmp(ptr,"DEFAULT=",8) == 0) {
      ptr+=8;
      D(("Default arg found: <%s>", ptr));
      valptr=&(var->defval);
    } else if (strncmp(ptr, "OVERRIDE=", 9) == 0) {
      ptr+=9;
      D(("Override arg found: <%s>", ptr));
      valptr=&(var->override);
    } else {
      D(("Unrecognized options: <%s> - ignoring line", ptr));
      pam_syslog(pamh, LOG_ERR, "Unrecognized Option: %s - ignoring line", ptr);
      return BAD_LINE;
    }

    if ('"' != *ptr) {
      length = strcspn(ptr, " \t\n");
      tmpptr = ptr+length;
    } else {
      tmpptr = strchr(++ptr, '"');
      if (!tmpptr) {
	D(("Unterminated quoted string: %s", ptr-1));
	pam_syslog(pamh, LOG_ERR, "Unterminated quoted string: %s", ptr-1);
	return BAD_LINE;
      }
      length = tmpptr - ptr;
      if (*++tmpptr && ' ' != *tmpptr && '\t' != *tmpptr && '\n' != *tmpptr) {
	D(("Quotes must cover the entire string: <%s>", ptr));
	pam_syslog(pamh, LOG_ERR, "Quotes must cover the entire string: <%s>", ptr);
	return BAD_LINE;
      }
      quoteflg++;
    }
    if (length) {
      if ((*valptr = malloc(length + 1)) == NULL) {
	D(("Couldn't malloc %d bytes", length+1));
	pam_syslog(pamh, LOG_ERR, "Couldn't malloc %d bytes", length+1);
	return PAM_BUF_ERR;
      }
      (void)strncpy(*valptr,ptr,length);
      (*valptr)[length]='\0';
    } else if (quoteflg--) {
      *valptr = &quote;
    }
    ptr = tmpptr;
  }


  D(("Exit."));
  ptr = NULL; tmpptr = NULL; valptr = NULL;
  return GOOD_LINE;
}
