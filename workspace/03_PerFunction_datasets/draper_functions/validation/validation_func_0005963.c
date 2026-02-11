makeboot (analdef *adef, rawdata *rdta, cruncheddata *cdta)
  {
    int  i, j, nonzero;
    double  randum();

    nonzero = 0;
    for (i = 1; i <= rdta->sites; i++)  if (rdta->wgt[i] > 0) nonzero++;

    for (j = 1; j <= nonzero; j++) cdta->aliaswgt[j] = 0;
    for (j = 1; j <= nonzero; j++)
      cdta->aliaswgt[(int) (nonzero*randum(& adef->boot)) + 1]++;

    j = 0;
    cdta->wgtsum = 0;
    for (i = 1; i <= rdta->sites; i++) {
      if (rdta->wgt[i] > 0)
        cdta->wgtsum += (rdta->wgt2[i] = rdta->wgt[i] * cdta->aliaswgt[++j]);
      else
        rdta->wgt2[i] = 0;
      }
  }
