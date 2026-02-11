set_lflags(MAILSTREAM *stream, MSGNO_S *msgmap, int f, int v)
{
    unsigned long i;

    if((v == 0 && any_lflagged(msgmap, f)) || v )
      for(i = 1L; i <= mn_get_total(msgmap); i++)
	set_lflag(stream, msgmap, i, f, v);
}
