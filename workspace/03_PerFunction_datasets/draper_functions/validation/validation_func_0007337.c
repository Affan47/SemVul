mbe_eccImbe7200x4400Data (char imbe_fr[8][23], char *imbe_d)
{

  int i, j, errs;
  char *imbe, gin[23], gout[23], hin[15], hout[15];

  errs = 0;
  imbe = imbe_d;
  for (i = 0; i < 4; i++)
    {
      if (i > 0)
        {
          for (j = 0; j < 23; j++)
            {
              gin[j] = imbe_fr[i][j];
            }
          errs += mbe_golay2312 (gin, gout);
          for (j = 22; j > 10; j--)
            {
              *imbe = gout[j];
              imbe++;
            }
        }
      else
        {
          for (j = 22; j > 10; j--)
            {
              *imbe = imbe_fr[i][j];
              imbe++;
            }
        }
    }
  for (i = 4; i < 7; i++)
    {
      for (j = 0; j < 15; j++)
        {
          hin[j] = imbe_fr[i][j];
        }
      errs += mbe_hamming1511 (hin, hout);
      for (j = 14; j >= 4; j--)
        {
          *imbe = hout[j];
          imbe++;
        }
    }
  for (j = 6; j >= 0; j--)
    {
      *imbe = imbe_fr[7][j];
      imbe++;
    }

  return (errs);
}
