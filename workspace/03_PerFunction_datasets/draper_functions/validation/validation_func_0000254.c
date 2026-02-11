cm_SetConsensus(CM_t *cm, CMConsensus_t *cons, ESL_SQ *sq)
{
  int   status;
  int   cpos;

  if(cons == NULL || sq != NULL) { status = eslEINVAL; goto ERROR; }


  if (! cm->consensus) ESL_ALLOC(cm->consensus, sizeof(char) * (cm->clen+2));


  cm->consensus[0] = ' ';
  for (cpos = 1; cpos <= cm->clen; cpos++) cm->consensus[cpos] = cons->cseq[cpos-1];
  cm->consensus[cm->clen+1] = '\0';
  cm->flags  |= CMH_CONS;
  return eslOK;

 ERROR:
  if (cm->consensus) free(cm->consensus);
  cm->consensus = NULL;
  cm->flags    &= (~CMH_CONS);
  return status;
}
