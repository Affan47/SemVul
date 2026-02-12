void imap_get_parent(char *output, const char *mbox, size_t olen, char delim)
{
  int n;


  if (mbox != output)
    mutt_str_strfcpy(output, mbox, olen);

  n = mutt_str_strlen(output);


  for (n--; n >= 0 && output[n] != delim; n--)
    ;


  if (n > 0)
  {

    output[n] = '\0';
  }
  else
  {
    output[0] = (n == 0) ? delim : '\0';
  }
}
