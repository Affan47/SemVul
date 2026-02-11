printFasta(FILE* f, GStr& defline, char* seq, int seqlen) {
 if (seq==NULL) return;
 int len=(seqlen>0)?seqlen:strlen(seq);
 if (len<=0) return;
 if (!defline.is_empty())
     fprintf(f, ">%s\n",defline.chars());
 int ilen=0;
 for (int i=0; i < len; i++, ilen++) {
   if (ilen == 70) {
     fputc('\n', f);
     ilen = 0;
     }
   putc(seq[i], f);
   }
 fputc('\n', f);
}
