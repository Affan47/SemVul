read_message_data_smtp(FILE *fout)
{
int ch_state = 0;
int ch;
int linelength = 0;

while ((ch = (receive_getc)(GETC_BUFFER_UNLIMITED)) != EOF)
  {
  if (ch == 0) body_zerocount++;
  switch (ch_state)
    {
    case 0:
    if (ch == '.')
      {
      ch_state = 3;
      continue;
      }
    ch_state = 1;


    case 1:
    if (ch == '\n')
      {
      ch_state = 0;
      body_linecount++;
      if (linelength > max_received_linelength)
        max_received_linelength = linelength;
      linelength = -1;
      }
    else if (ch == '\r')
      {
      ch_state = 2;
      continue;
      }
    break;

    case 2:
    body_linecount++;
    if (linelength > max_received_linelength)
      max_received_linelength = linelength;
    linelength = -1;
    if (ch == '\n')
      {
      ch_state = 0;
      }
    else
      {
      message_size++;
      if (fout != NULL && fputc('\n', fout) == EOF) return END_WERROR;
      cutthrough_data_put_nl();
      if (ch != '\r') ch_state = 1; else continue;
      }
    break;

    case 3:
    if (ch == '\n')
      return END_DOT;
    if (ch == '\r')
      {
      ch_state = 4;
      continue;
      }


    if (ch == '.')
      {
      uschar c= ch;
      cutthrough_data_puts(&c, 1);
      }
    ch_state = 1;
    break;

    case 4:
    if (ch == '\n') return END_DOT;
    message_size++;
    body_linecount++;
    if (fout != NULL && fputc('\n', fout) == EOF) return END_WERROR;
    cutthrough_data_put_nl();
    if (ch == '\r')
      {
      ch_state = 2;
      continue;
      }
    ch_state = 1;
    break;
    }


  message_size++;
  linelength++;
  if (fout)
    {
    if (fputc(ch, fout) == EOF) return END_WERROR;
    if (message_size > thismessage_size_limit) return END_SIZE;
    }
  if(ch == '\n')
    cutthrough_data_put_nl();
  else
    {
    uschar c = ch;
    cutthrough_data_puts(&c, 1);
    }
  }


return END_EOF;
}
