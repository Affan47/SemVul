Init(long *ChOrder, long *Count, long *MaxChars, aPtr aChars)
{

  long i, j, temp;
  boolean instate;

  *MaxChars = 0;
  for (i = 1; i <= (chars); i++) {
    if (aChars[ActChar[i - 1] - 1]) {
      (*MaxChars)++;
      ChOrder[*MaxChars - 1] = i;
      instate = Ingroupstate(i);
      temp = 0;
      for (j = 0; j < (spp); j++) {
        if (Data[j]->vec[i - 1] == instate)
          temp++;
      }
      Count[i - 1] = temp;
    }
  }
}
