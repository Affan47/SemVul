void AAHD::evaluate_ahd()
{
  int hvdir[4] = {Pw, Pe, Pn, Ps};


  for (int d = 0; d < 2; ++d)
  {
    for (int i = 0; i < nr_width * nr_height; ++i)
    {
      ushort3 rgb;
      for (int c = 0; c < 3; ++c)
      {
        rgb[c] = gammaLUT[rgb_ahd[d][i][c]];
      }
      yuv[d][i][0] = Y(rgb);
      yuv[d][i][1] = U(rgb);
      yuv[d][i][2] = V(rgb);
    }
  }


  for (int i = 0; i < libraw.imgdata.sizes.iheight; ++i)
  {
    int moff = nr_offset(i + nr_margin, nr_margin);
    for (int j = 0; j < libraw.imgdata.sizes.iwidth; j++, ++moff)
    {
      int3 *ynr;
      float ydiff[2][4];
      int uvdiff[2][4];
      for (int d = 0; d < 2; ++d)
      {
        ynr = &yuv[d][moff];
        for (int k = 0; k < 4; k++)
        {
          ydiff[d][k] = ABS(ynr[0][0] - ynr[hvdir[k]][0]);
          uvdiff[d][k] = SQR(ynr[0][1] - ynr[hvdir[k]][1]) +
                         SQR(ynr[0][2] - ynr[hvdir[k]][2]);
        }
      }
      float yeps =
          MIN(MAX(ydiff[0][0], ydiff[0][1]), MAX(ydiff[1][2], ydiff[1][3]));
      int uveps =
          MIN(MAX(uvdiff[0][0], uvdiff[0][1]), MAX(uvdiff[1][2], uvdiff[1][3]));
      for (int d = 0; d < 2; d++)
      {
        ynr = &yuv[d][moff];
        for (int k = 0; k < 4; k++)
          if (ydiff[d][k] <= yeps && uvdiff[d][k] <= uveps)
          {
            homo[d][moff + hvdir[k]]++;
            if (k / 2 == d)
            {


              for (int m = 2; m < 4; ++m)
              {
                int hvd = m * hvdir[k];
                if (ABS(ynr[0][0] - ynr[hvd][0]) < yeps &&
                    SQR(ynr[0][1] - ynr[hvd][1]) +
                            SQR(ynr[0][2] - ynr[hvd][2]) <
                        uveps)
                {
                  homo[d][moff + hvd]++;
                }
                else
                  break;
              }
            }
          }
      }
    }
  }
  for (int i = 0; i < libraw.imgdata.sizes.iheight; ++i)
  {
    int moff = nr_offset(i + nr_margin, nr_margin);
    for (int j = 0; j < libraw.imgdata.sizes.iwidth; j++, ++moff)
    {
      char hm[2];
      for (int d = 0; d < 2; d++)
      {
        hm[d] = 0;
        char *hh = &homo[d][moff];
        for (int hx = -1; hx < 2; hx++)
          for (int hy = -1; hy < 2; hy++)
            hm[d] += hh[nr_offset(hy, hx)];
      }
      char d = 0;
      if (hm[0] != hm[1])
      {
        if (hm[1] > hm[0])
        {
          d = VERSH;
        }
        else
        {
          d = HORSH;
        }
      }
      else
      {
        int3 *ynr = &yuv[1][moff];
        int gv = SQR(2 * ynr[0][0] - ynr[Pn][0] - ynr[Ps][0]);
        gv += SQR(2 * ynr[0][1] - ynr[Pn][1] - ynr[Ps][1]) +
              SQR(2 * ynr[0][2] - ynr[Pn][2] - ynr[Ps][2]);
        ynr = &yuv[1][moff + Pn];
        gv += (SQR(2 * ynr[0][0] - ynr[Pn][0] - ynr[Ps][0]) +
               SQR(2 * ynr[0][1] - ynr[Pn][1] - ynr[Ps][1]) +
               SQR(2 * ynr[0][2] - ynr[Pn][2] - ynr[Ps][2])) /
              2;
        ynr = &yuv[1][moff + Ps];
        gv += (SQR(2 * ynr[0][0] - ynr[Pn][0] - ynr[Ps][0]) +
               SQR(2 * ynr[0][1] - ynr[Pn][1] - ynr[Ps][1]) +
               SQR(2 * ynr[0][2] - ynr[Pn][2] - ynr[Ps][2])) /
              2;
        ynr = &yuv[0][moff];
        int gh = SQR(2 * ynr[0][0] - ynr[Pw][0] - ynr[Pe][0]);
        gh += SQR(2 * ynr[0][1] - ynr[Pw][1] - ynr[Pe][1]) +
              SQR(2 * ynr[0][2] - ynr[Pw][2] - ynr[Pe][2]);
        ynr = &yuv[0][moff + Pw];
        gh += (SQR(2 * ynr[0][0] - ynr[Pw][0] - ynr[Pe][0]) +
               SQR(2 * ynr[0][1] - ynr[Pw][1] - ynr[Pe][1]) +
               SQR(2 * ynr[0][2] - ynr[Pw][2] - ynr[Pe][2])) /
              2;
        ynr = &yuv[0][moff + Pe];
        gh += (SQR(2 * ynr[0][0] - ynr[Pw][0] - ynr[Pe][0]) +
               SQR(2 * ynr[0][1] - ynr[Pw][1] - ynr[Pe][1]) +
               SQR(2 * ynr[0][2] - ynr[Pw][2] - ynr[Pe][2])) /
              2;
        if (gv > gh)
          d = HOR;
        else
          d = VER;
      }
      ndir[moff] |= d;
    }
  }
}
