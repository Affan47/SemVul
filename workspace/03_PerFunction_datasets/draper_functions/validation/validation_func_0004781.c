ifile_lexer_simple_get_word (ifile_lexer *self, ifile_lex *lex,
			     char *buf, int buflen)
{
  int wordlen;

  do
    {
      wordlen = ifile_lexer_simple_get_raw_word ((ifile_lexer_simple*)self,
					       lex, buf, buflen);
      if (wordlen == 0)
	return 0;
    }
  while ((wordlen = ifile_lexer_simple_postprocess_word
	  ((ifile_lexer_simple*)self, lex, buf, buflen))
	 == 0);
  return wordlen;
}
