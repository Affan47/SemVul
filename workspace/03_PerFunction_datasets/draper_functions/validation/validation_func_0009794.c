phase4_get (token_ty *tp)
{
  if (phase4_pushback_length)
    {
      *tp = phase4_pushback[--phase4_pushback_length];
      phase4_last = tp->type;
      return;
    }

  phase3_get (tp);
  if (tp->type == token_type_string
      && !(phase4_last == token_type_operator1
           || phase4_last == token_type_dot
           || phase4_last == token_type_symbol
           || phase4_last == token_type_doubledot
           || phase4_last == token_type_rparen))
    {
      char *sum = tp->string;
      size_t sum_len = strlen (sum);

      for (;;)
        {
          token_ty token2;

          phase3_get (&token2);
          if (token2.type == token_type_doubledot)
            {
              token_ty token3;

              phase3_get (&token3);
              if (token3.type == token_type_string)
                {
                  token_ty token_after;

                  phase3_get (&token_after);
                  if (token_after.type != token_type_operator1)
                    {
                      char *addend = token3.string;
                      size_t addend_len = strlen (addend);

                      sum = (char *) xrealloc (sum, sum_len + addend_len + 1);
                      memcpy (sum + sum_len, addend, addend_len + 1);
                      sum_len += addend_len;

                      phase3_unget (&token_after);
                      free_token (&token3);
                      free_token (&token2);
                      continue;
                    }
                  phase3_unget (&token_after);
                }
              phase3_unget (&token3);
            }
          phase3_unget (&token2);
          break;
        }
      tp->string = sum;
    }
  phase4_last = tp->type;
}
