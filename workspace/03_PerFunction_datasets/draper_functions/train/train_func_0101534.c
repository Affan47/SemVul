crypto_make_random_string_from_template(char *template)
{
  char *t;
  unsigned int count;
  Ds ds;

  ds_init(&ds);
  for (t = template; *t != '\0'; t++) {
	if (*t == '%') {
	  if (*(t + 1) != '\0')
		t++;
	  if (isdigit((int) *t)) {
		char *endp;

		if (strnumx(t, STRNUM_UI, &count, &endp) == -1)
		  return(NULL);
		t = endp;
	  }
	  else
		count = 1;

	  if (append_random_chars(&ds, (int) *t, count) == -1)
		return(NULL);
	}
	else
	  ds_appendc(&ds, (int) *t);
  }

  ds_appendc(&ds, (int) '\0');

  return(ds_buf(&ds));
}
