static char *parse_params(
                          imp_xxh_t *imp_xxh,
                          pTHX_ MYSQL *sock,
                          char *statement,
                          STRLEN *slen_ptr,
                          imp_sth_ph_t* params,
                          int num_params,
                          bool bind_type_guessing,
                          bool bind_comment_placeholders)
{
  bool comment_end= false;
  char *salloc, *statement_ptr;
  char *statement_ptr_end, *ptr, *valbuf;
  char *cp, *end;
  int alen, i;
  int slen= *slen_ptr;
  int limit_flag= 0;
  int comment_length=0;
  STRLEN vallen;
  imp_sth_ph_t *ph;

  if (DBIc_DBISTATE(imp_xxh)->debug >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh), ">parse_params statement %s\n", statement);

  if (num_params == 0)
    return NULL;

  while (isspace(*statement))
  {
    ++statement;
    --slen;
  }


  alen= slen;

  for (i= 0, ph= params; i < num_params; i++, ph++)
  {
    int defined= 0;
    if (ph->value)
    {
      if (SvMAGICAL(ph->value))
        mg_get(ph->value);
      if (SvOK(ph->value))
        defined=1;
    }
    if (!defined)
      alen+= 3;
    else
    {
      valbuf= SvPV(ph->value, vallen);
      alen+= 2+vallen+1;


      if (!ph->type)
      {
        if (bind_type_guessing)
        {
          valbuf= SvPV(ph->value, vallen);
          ph->type= SQL_INTEGER;

          if (parse_number(valbuf, vallen, &end) != 0)
          {
              ph->type= SQL_VARCHAR;
          }
        }
        else
          ph->type= SQL_VARCHAR;
      }
    }
  }


  New(908, salloc, alen*2, char);
  ptr= salloc;

  i= 0;

  statement_ptr_end= (statement_ptr= statement)+ slen;

  while (statement_ptr < statement_ptr_end)
  {

    if (! limit_flag)
    {


      if ((*statement_ptr == 'l' || *statement_ptr == 'L') &&
          (!strncmp(statement_ptr+1, "imit ?", 6) ||
           !strncmp(statement_ptr+1, "IMIT ?", 6)))
      {
        limit_flag = 1;
      }
    }
    switch (*statement_ptr)
    {

      case '-':
      {
          if (bind_comment_placeholders)
          {
              *ptr++= *statement_ptr++;
              break;
          }
          else
          {
              comment_length= 1;
              comment_end= false;
              *ptr++ = *statement_ptr++;
              if  (*statement_ptr == '-')
              {

                  while (*statement_ptr)
                  {
                      comment_length++;
                      *ptr++ = *statement_ptr++;
                      if (!*statement_ptr || *statement_ptr == '\n')
                      {
                          comment_end= true;
                          break;
                      }
                  }

                  if (! comment_end)
                  {
                      statement_ptr -= comment_length;
                      ptr -= comment_length;
                  }
              }
              break;
          }
      }

      case '/':
      {
          if (bind_comment_placeholders)
          {
              *ptr++= *statement_ptr++;
              break;
          }
          else
          {
              comment_length= 1;
              comment_end= false;
              *ptr++ = *statement_ptr++;
              if  (*statement_ptr == '*')
              {

                  while (*statement_ptr)
                  {
                      *ptr++ = *statement_ptr++;
                      comment_length++;
                      if (!strncmp(statement_ptr, "*/", 2))
                      {
                          comment_length += 2;
                          comment_end= true;
                          break;
                      }
                  }

                  if (! comment_end)
                  {
                      statement_ptr -= comment_length;
                      ptr -= comment_length;
                  }
              }
              break;
          }
      }
      case '`':
      case '\'':
      case '"':

      {
        char endToken = *statement_ptr++;
        *ptr++ = endToken;
        while (statement_ptr != statement_ptr_end &&
               *statement_ptr != endToken)
        {
          if (*statement_ptr == '\\')
          {
            *ptr++ = *statement_ptr++;
            if (statement_ptr == statement_ptr_end)
	      break;
	  }
          *ptr++= *statement_ptr++;
	}
	if (statement_ptr != statement_ptr_end)
          *ptr++= *statement_ptr++;
      }
      break;

      case '?':

        statement_ptr++;
        if (i >= num_params)
        {
          break;
        }

        ph = params+ (i++);
        if (!ph->value  ||  !SvOK(ph->value))
        {
          *ptr++ = 'N';
          *ptr++ = 'U';
          *ptr++ = 'L';
          *ptr++ = 'L';
        }
        else
        {
          int is_num = FALSE;

          valbuf= SvPV(ph->value, vallen);
          if (valbuf)
          {
            switch (ph->type)
            {
              case SQL_NUMERIC:
              case SQL_DECIMAL:
              case SQL_INTEGER:
              case SQL_SMALLINT:
              case SQL_FLOAT:
              case SQL_REAL:
              case SQL_DOUBLE:
              case SQL_BIGINT:
              case SQL_TINYINT:
                is_num = TRUE;
                break;
            }


            if ( parse_number(valbuf, vallen, &end) != 0 && is_num)
            {
              if (bind_type_guessing) {

                is_num = 0;
                ph->type = SQL_VARCHAR;
              }
            }


            if (limit_flag == 1)
              is_num = TRUE;

            if (!is_num)
            {
              *ptr++ = '\'';
              ptr += mysql_real_escape_string(sock, ptr, valbuf, vallen);
              *ptr++ = '\'';
            }
            else
            {
              for (cp= valbuf; cp < end; cp++)
                  *ptr++= *cp;
            }
          }
        }
        break;


      case ')':
        limit_flag = 0;
	*ptr++ = *statement_ptr++;
        break;

      default:
        *ptr++ = *statement_ptr++;
        break;

    }
  }

  *slen_ptr = ptr - salloc;
  *ptr++ = '\0';

  return(salloc);
}
