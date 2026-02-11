ProcessContext(void)
{
  if (C->len==0) { C->buf[0]='\n'; C->len++; }
  while (!C->eof) ParseText();
  if (C->in!=NULL) fclose(C->in);
  free(C->malloced_buf);
}
