count_params(imp_xxh_t *imp_xxh, pTHX_ char *statement, bool bind_comment_placeholders)
{
  bool comment_end= false;
  char* ptr= statement;
  int num_params= 0;
  int comment_length= 0;
  char c;

  if (DBIc_DBISTATE(imp_xxh)->debug >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh), ">count_params statement %s\n", statement);

  while ( (c = *ptr++) )
  {
    switch (c) {

    case '-':
      {
          if (bind_comment_placeholders)
          {
              c = *ptr++;
              break;
          }
          else
          {
              comment_length= 1;

              c = *ptr++;

              if  (c == '-') {

                  while ((c = *ptr))
                  {
                      if (DBIc_DBISTATE(imp_xxh)->debug >= 2)
                          PerlIO_printf(DBIc_LOGPIO(imp_xxh), "%c\n", c);
                      ptr++;
                      comment_length++;
                      if (c == '\n')
                      {
                          comment_end= true;
                          break;
                      }
                  }


                  if (! comment_end)
                      ptr-= comment_length;
              }

              else
                  ptr--;
              break;
          }
      }

    case '/':
      {
          if (bind_comment_placeholders)
          {
              c = *ptr++;
              break;
          }
          else
          {
              c = *ptr++;

              if  (c == '*')
              {
                  comment_length= 0;
                  comment_end= false;

                  while ((c= *ptr))
                  {
                      ptr++;
                      comment_length++;

                      if (c == '*')
                      {
                          c = *ptr++;

                          if (c == '/')
                          {
                              comment_end= true;
                              break;
                          }


                          else
                              ptr--;
                      }
                  }


                  if (!comment_end)
                      ptr -= comment_length;
              }
              else
                  ptr--;
              break;
          }
      }
    case '`':
    case '"':
    case '\'':

      {
        char end_token = c;
        while ((c = *ptr)  &&  c != end_token)
        {
          if (c == '\\')
            if (! *(++ptr))
              continue;

          ++ptr;
        }
        if (c)
          ++ptr;
        break;
      }

    case '?':
      ++num_params;
      break;

    default:
      break;
    }
  }
  return num_params;
}
