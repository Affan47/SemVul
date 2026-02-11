mirror() const
{
  AIBoard other;
  other.mCurrent = mCurrent;


  for (int y=0;y<=5;y++)
  {
    ushort tmp  = mBoard[y];
    ushort ntmp = 0;

    for (int x=0; x<=6; x++)
    {
      ntmp = ntmp << 2;
      ntmp |= (tmp >> (x<<1)) & 3;
    }
    other.mBoard[y] = ntmp;
  }
  return other;
}
