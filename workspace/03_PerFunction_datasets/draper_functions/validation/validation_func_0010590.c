new_context (void)
{
  int i;

  for (i = 0; i < MAX_CONTEXT; i++)
    if (contexts[i].buflen == 0) {
      struct context *c = &contexts[i];

      if ((c->buf = (unsigned char *)malloc (INITIAL_BUFLEN)) == NULL)
	return -1;

      if ((c->selection = (int *)malloc (INITIAL_SELLEN)) == NULL) {
	free (c->buf);
	c->buf = NULL;
	return -1;
      }

      if ((c->ac = anthy_create_context ()) == NULL) {
	free (c->buf);
	c->buf = NULL;
	free (c->selection);
	c->selection = NULL;
	return -1;
      }
      if (use_utf8) {
	anthy_context_set_encoding(c->ac, ANTHY_UTF8_ENCODING);
      }

      c->buflen = INITIAL_BUFLEN;
      c->sellen = INITIAL_SELLEN;
      return i;
    }


  return -1;
}
