bufNum(int size)
{
  if(size<=8)return 0;
  int ret=0;
  while(size>8)
    {
      ret++;
      if(ret>=(NBUCKETSGMP))return -1;
      size>>1;
    }
  return ret;
}
