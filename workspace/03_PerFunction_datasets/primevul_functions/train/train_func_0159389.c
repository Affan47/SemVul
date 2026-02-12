read_message_bdat_smtp_wire(FILE *fout)
{
int ch;


DEBUG(D_receive) debug_printf("CHUNKING: writing spoolfile in wire format\n");
spool_file_wireformat = TRUE;

for (;;)
  {
  if (chunking_data_left > 0)
    {
    unsigned len = MAX(chunking_data_left, thismessage_size_limit - message_size + 1);
    uschar * buf = bdat_getbuf(&len);

    message_size += len;
    if (fout && fwrite(buf, len, 1, fout) != 1) return END_WERROR;
    }
  else switch (ch = bdat_getc(GETC_BUFFER_UNLIMITED))
    {
    case EOF: return END_EOF;
    case EOD: return END_DOT;
    case ERR: return END_PROTOCOL;

    default:
      message_size++;


      if (fout && fputc(ch, fout) == EOF) return END_WERROR;
      break;
    }
  if (message_size > thismessage_size_limit) return END_SIZE;
  }

}
