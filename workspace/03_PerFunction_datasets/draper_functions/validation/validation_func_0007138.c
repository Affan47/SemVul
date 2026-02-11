readtokens (FILE *stream,
            size_t projected_n_tokens,
            const char *delim,
            size_t n_delim,
            char ***tokens_out,
            size_t **token_lengths)
{
  token_buffer tb, *token = &tb;
  char **tokens;
  size_t *lengths;
  size_t sz;
  size_t n_tokens;

  if (projected_n_tokens == 0)
    projected_n_tokens = 64;
  else
    projected_n_tokens++;

  sz = projected_n_tokens;
  tokens = xnmalloc (sz, sizeof *tokens);
  lengths = xnmalloc (sz, sizeof *lengths);

  n_tokens = 0;
  init_tokenbuffer (token);
  for (;;)
    {
      char *tmp;
      size_t token_length = readtoken (stream, delim, n_delim, token);
      if (n_tokens >= sz)
        {
          tokens = x2nrealloc (tokens, &sz, sizeof *tokens);
          lengths = xnrealloc (lengths, sz, sizeof *lengths);
        }

      if (token_length == (size_t) -1)
        {

          tokens[n_tokens] = NULL;
          lengths[n_tokens] = 0;
          break;
        }
      tmp = xnmalloc (token_length + 1, sizeof *tmp);
      lengths[n_tokens] = token_length;
      tokens[n_tokens] = memcpy (tmp, token->buffer, token_length + 1);
      n_tokens++;
    }

  free (token->buffer);
  *tokens_out = tokens;
  if (token_lengths != NULL)
    *token_lengths = lengths;
  else
    free (lengths);
  return n_tokens;
}
