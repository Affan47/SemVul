writefactors(void)
{
  long k, l, m, n, prevfact, writesites;
  char symbol;
  steptr wfactor;

  if(!justwts || firstrep){
    if(justwts){
      writesites = sites;
      wfactor = factorr;
    } else {
      writesites = newersites;
      wfactor = newerfactor;
    }
    prevfact = wfactor[0];
    symbol = '+';
    if (interleaved)
      m = 60;
    else
      m = writesites;
    l=1;
    do {
      if(m > writesites)
        m = writesites;
      n = 0;
      for(k=l-1 ; k < m ; k++){
        n++;
        if (!interleaved && n > 1 && n % 60 == 1)
          fprintf(outfactfile, "\n ");
        if(prevfact != wfactor[k]){
          symbol = (symbol == '+') ? '-' : '+';
          prevfact = wfactor[k];
        }
        putc(symbol, outfactfile);
        if (n % 10 == 0 && n % 60 != 0)
          putc(' ', outfactfile);
      }
      if (interleaved) {
        l += 60;
        m += 60;
      }
    }while(interleaved && l <= writesites);
    fprintf(outfactfile, "\n");
  }
}
