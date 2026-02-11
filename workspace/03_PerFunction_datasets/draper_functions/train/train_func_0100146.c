pos_tokenize (const char  *expr,
              PosToken   **tokens_p,
              int         *n_tokens_p,
              GError     **err)
{
  PosToken *tokens;
  int n_tokens;
  int allocated;
  const char *p;

  *tokens_p = NULL;
  *n_tokens_p = 0;

  allocated = 3;
  n_tokens = 0;
  tokens = g_new (PosToken, allocated);

  p = expr;
  while (*p)
    {
      PosToken *next;
      int len;

      if (n_tokens == allocated)
        {
          allocated *= 2;
          tokens = g_renew (PosToken, tokens, allocated);
        }

      next = &tokens[n_tokens];

      switch (*p)
        {
        case '*':
        case '/':
        case '+':
        case '-':
        case '%':
        case '`':
          next->type = POS_TOKEN_OPERATOR;
          next->d.o.op = op_from_string (p, &len);
          if (next->d.o.op != POS_OP_NONE)
            {
              ++n_tokens;
              p = p + (len - 1);
            }
          else
            {
              g_set_error (err, META_THEME_ERROR,
                           META_THEME_ERROR_FAILED,
                           _("Coordinate expression contained unknown operator at the start of this text: \"%s\""),
                           p);

              goto error;
            }
          break;

        case '(':
          next->type = POS_TOKEN_OPEN_PAREN;
          ++n_tokens;
          break;

        case ')':
          next->type = POS_TOKEN_CLOSE_PAREN;
          ++n_tokens;
          break;

        case ' ':
        case '\t':
        case '\n':
          break;

        default:
          if (IS_VARIABLE_CHAR (*p))
            {

              const char *start = p;
              while (*p && IS_VARIABLE_CHAR (*p))
                ++p;
              g_assert (p != start);
              next->type = POS_TOKEN_VARIABLE;
              next->d.v.name = g_strndup (start, p - start);
              ++n_tokens;
              --p;
            }
          else
            {

              const char *end;

              if (!parse_number (p, &end, next, err))
                goto error;

              ++n_tokens;
              p = end - 1;
            }

          break;
        }

      ++p;
    }

  if (n_tokens == 0)
    {
      g_set_error (err, META_THEME_ERROR,
                   META_THEME_ERROR_FAILED,
                   _("Coordinate expression was empty or not understood"));

      goto error;
    }

  *tokens_p = tokens;
  *n_tokens_p = n_tokens;

  return TRUE;

 error:
  g_assert (err == NULL || *err != NULL);

  free_tokens (tokens, n_tokens);
  return FALSE;
}
