setupmem(struct state *st)
{
  int i;
  for (i=0;i<MAXFRAMES;i++) {
    if((st->exponents[i]=
        (double *)malloc(sizeof(double)*st->width*(st->height+1)))==NULL){
      fprintf(stderr,"Error malloc'ing exponent array.\n");
      exit(-1);
    }
  }
}
