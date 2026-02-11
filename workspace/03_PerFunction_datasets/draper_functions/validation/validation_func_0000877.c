var_figure(char* h, int script)
{
  char* word = NULL;
  int ret = 0;
  int n1 = 0, n2 = 0;

  int is_one_word_equation = 0;
  word = get_word(h, 2);
  if (compare(word, ""))
    is_one_word_equation = 1;
  free(word);
  if (is_one_word_equation)
    {

      if (h[0] == '&')
	decipher_string(&h, script);


      ret = atol(h);
      return ret;
    }

  word = get_word(h, 1);
  decipher_string(&word, script);
  n1 = atol(word);
  free(word);

  word = get_word(h, 3);
  replace_norealloc(")", "", word);
  decipher_string(&word, script);
  n2 = atol(word);
  free(word);

  word = get_word(h, 2);
  log_debug("Compared %d to %d", n1, n2);

  if (compare(word, "=="))
    {
      if (n1 == n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }

  if (compare(word, ">"))
    {
      if (n1 > n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }

  if (compare(word, ">="))
    {
      if (n1 >= n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }


  if (compare(word, "<"))
    {
      if (n1 < n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }

  if (compare(word, "<="))
    {
      if (n1 <= n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }

  if (compare(word, "!="))
    {
      if (n1 != n2) ret = 1; else ret = 0;
      free(word);
      return ret;
    }

  free(word);
  return ret;
}
