countObsList(header)
Cell header;
{
    Int seq, n=0;
    Cell j;

    for (j=firstObs(header); j!=header; j=nextObs(j)) {
        seq  = intOf(seqObs(j));
        if (seq < 0) {
            n++;
        } else if (seq!=0) {
	   if (whatIs(exprObs(j)) == OBSERVEHEAD) {
	       n += countObsList(exprObs(j));
           } else {
	       n++;
	   }
	}
    }
    return n;
}
