readEMBL(struct ReadSeqVars *V)
{
  char *sptr;
  int   i;


  while (!feof(V->f) && strncmp(V->buf, "ID  ", 4) != 0) {
    SeqfileGetLine(V);
  }
  if (V->ssimode >= 0) V->r_off = V->ssioffset;

  if ((sptr = strtok(V->buf+5, "\n\t ")) != NULL)
    {
      SetSeqinfoString(V->sqinfo, sptr, SQINFO_NAME);
      SetSeqinfoString(V->sqinfo, sptr, SQINFO_ID);
    }

  do {
    SeqfileGetLine(V);
    if (!feof(V->f) && strstr(V->buf, "AC  ") == V->buf)
      {
	if ((sptr = strtok(V->buf+5, ";  \t\n")) != NULL)
	  SetSeqinfoString(V->sqinfo, sptr, SQINFO_ACC);
      }
    else if (!feof(V->f) && strstr(V->buf, "DE  ") == V->buf)
      {
	if ((sptr = strtok(V->buf+5, "\n")) != NULL)
	  SetSeqinfoString(V->sqinfo, sptr, SQINFO_DESC);
      }
  } while (! feof(V->f) && strncmp(V->buf,"SQ",2) != 0);

  readLoop(0, endEMBL, V);


  if (V->ssimode == -1)
    for (i = 0; i < V->seqlen; i++)
      if (V->seq[i] == '-') V->seq[i] = 'N';


  V->sqinfo->start = 1;
  V->sqinfo->stop  = V->seqlen;
  V->sqinfo->olen  = V->seqlen;
  V->sqinfo->flags |= SQINFO_START | SQINFO_STOP | SQINFO_OLEN;


  while (!feof(V->f) && strncmp(V->buf, "ID  ", 4) != 0) {
    SeqfileGetLine(V);
  }

}
