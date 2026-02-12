void LibRaw::adjust_bl()
{
  int clear_repeat = 0;
  if (O.user_black >= 0)
  {
    C.black = O.user_black;
    clear_repeat = 1;
  }
  for (int i = 0; i < 4; i++)
    if (O.user_cblack[i] > -1000000)
    {
      C.cblack[i] = O.user_cblack[i];
      clear_repeat = 1;
    }

  if (clear_repeat)
    C.cblack[4] = C.cblack[5] = 0;


  if (imgdata.idata.filters > 1000 && (C.cblack[4] + 1) / 2 == 1 &&
      (C.cblack[5] + 1) / 2 == 1)
  {
    int clrs[4];
    int lastg = -1, gcnt = 0;
    for (int c = 0; c < 4; c++)
    {
      clrs[c] = FC(c / 2, c % 2);
      if (clrs[c] == 1)
      {
        gcnt++;
        lastg = c;
      }
    }
    if (gcnt > 1 && lastg >= 0)
      clrs[lastg] = 3;
    for (int c = 0; c < 4; c++)
      C.cblack[clrs[c]] +=
          C.cblack[6 + c / 2 % C.cblack[4] * C.cblack[5] + c % 2 % C.cblack[5]];
    C.cblack[4] = C.cblack[5] = 0;

  }
  else if (imgdata.idata.filters <= 1000 && C.cblack[4] == 1 &&
           C.cblack[5] == 1)
  {
    for (int c = 0; c < 4; c++)
      C.cblack[c] += C.cblack[6];
    C.cblack[4] = C.cblack[5] = 0;
  }

  int i = C.cblack[3];
  int c;
  for (c = 0; c < 3; c++)
    if (i > C.cblack[c])
      i = C.cblack[c];

  for (c = 0; c < 4; c++)
    C.cblack[c] -= i;
  C.black += i;


  if (C.cblack[4] && C.cblack[5])
  {
    i = C.cblack[6];
    for (c = 1; c < C.cblack[4] * C.cblack[5]; c++)
      if (i > C.cblack[6 + c])
        i = C.cblack[6 + c];

    int nonz = 0;
    for (c = 0; c < C.cblack[4] * C.cblack[5]; c++)
    {
      C.cblack[6 + c] -= i;
      if (C.cblack[6 + c])
        nonz++;
    }
    C.black += i;
    if (!nonz)
      C.cblack[4] = C.cblack[5] = 0;
  }
  for (c = 0; c < 4; c++)
    C.cblack[c] += C.black;
}
