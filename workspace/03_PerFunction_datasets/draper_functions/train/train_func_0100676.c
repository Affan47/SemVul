compareORFs(const void *dataA, const void *dataB)
{
  MaximalORF *orfA = (MaximalORF*) dataA,
             *orfB = (MaximalORF*) dataB;
  gt_assert(orfA && orfB);
  if (orfA->lengthwithoutstopcodon > orfB->lengthwithoutstopcodon)
    return -1;
  else if (orfA->lengthwithoutstopcodon == orfB->lengthwithoutstopcodon) {
    if (orfA->framenum < orfB->framenum)
      return -1;
    else if (orfA->framenum == orfB->framenum)
      return 0;
    else
      return 1;
  }
  else
    return 1;
}
