jcf_print_utf8 (FILE *stream, const unsigned char *str, int length)
{
  const unsigned char * limit = str + length;
  while (str < limit)
    {
      int ch = UTF8_GET (str, limit);
      if (ch < 0)
	{
	  fprintf (stream, "\\<invalid>");
	  return;
	}
      jcf_print_char (stream, ch);
    }
}
