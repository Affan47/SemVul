_format_comment (pstdout_state_t pstate,
                 char *in,
                 char *out,
                 unsigned int outsize)
{
  char *inbuf = NULL;
  char *tokbuf;
  char *tok;
  int linelen = 0;
  int totalwritten = 0;
  int rv = -1;

  assert (in);
  assert (out);
  assert (outsize);

  if (!(inbuf = strdup (in)))
    goto cleanup;

  memset (out, '\0', outsize);


  if ((outsize - 1) <= (totalwritten + 2))
    goto cleanup;

  sprintf (out, "# ");
  totalwritten += 2;
  linelen += 2;

  tok = strtok_r (inbuf, " ", &tokbuf);
  while (tok)
    {
      int toklen = strlen (tok);

      if ((linelen + toklen) > FORMAT_COMMENT_COLUMN_WIDTH)
        {

          if ((outsize - 1) <= (totalwritten + 3))
            goto cleanup;

          strcat (out, "\n# ");
          totalwritten += 3;
          linelen = 2;
        }


      if ((outsize - 1) <= (totalwritten + toklen + 1))
        goto cleanup;

      strcat (out, tok);
      strcat (out, " ");
      totalwritten += (toklen + 1);
      linelen += (toklen + 1);

      tok = strtok_r (NULL, " ", &tokbuf);
    }


  if ((outsize -1) <= (totalwritten + 1))
    goto cleanup;

  strcat (out, "\n");

  rv = 0;
 cleanup:
  free (inbuf);
  return (rv);
}
