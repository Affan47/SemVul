Multiply4x4(const double a[16], const double b[16],
                               double c[16])
{
  SqMatPtr aMat = (SqMatPtr) a;
  SqMatPtr bMat = (SqMatPtr) b;
  SqMatPtr cMat = (SqMatPtr) c;
  int i, k;
  double Accum[4][4];

  for (i = 0; i < 4; i++)
    {
    for (k = 0; k < 4; k++)
      {
      Accum[i][k] = aMat[i][0] * bMat[0][k] +
                    aMat[i][1] * bMat[1][k] +
                    aMat[i][2] * bMat[2][k] +
                    aMat[i][3] * bMat[3][k];
      }
    }


  for (i = 0; i < 4; i++)
    {
    cMat[i][0] = Accum[i][0];
    cMat[i][1] = Accum[i][1];
    cMat[i][2] = Accum[i][2];
    cMat[i][3] = Accum[i][3];
    }

}
