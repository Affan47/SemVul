writeFasta(FILE *fw, const char* seqid, const char* descr,
        const char* seq, int linelen, int seqlen) {
  fflush(fw);

  if (seqid!=NULL) {
    if (descr==NULL || descr[0]==0)
             fprintf(fw,">%s\n",seqid);
        else fprintf(fw,">%s %s\n",seqid, descr);
    }
  fflush(fw);
  if (seq==NULL || *seq==0) return;
  if (linelen==0) {
     if (seqlen>0)
             fwrite((const void*)seq, 1, seqlen,fw);
        else fprintf(fw,"%s",seq);
     fprintf(fw,"\n");
     fflush(fw);
     return;
     }
  int ilen=0;
  if (seqlen>0) {
    for (int i=0; i < seqlen; i++, ilen++) {
            if (ilen == linelen) {
                 fputc('\n', fw);
                 ilen = 0;
                 }
            fputc(seq[i], fw);
            }
    fputc('\n', fw);
    }
  else {
    for (int i=0; seq[i]!=0; i++, ilen++) {
            if (ilen == linelen) {
                 fputc('\n', fw);
                 ilen = 0;
                 }
            fputc(seq[i], fw);
            }
    fputc('\n', fw);
    }
  fflush(fw);
 }
