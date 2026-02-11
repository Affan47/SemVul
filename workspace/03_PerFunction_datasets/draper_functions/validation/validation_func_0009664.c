blockLeft(unsigned target_,unsigned moveCount_)
{
  unsigned char *dp=data();
  for (unsigned i=target_;moveCount_>0;i++,moveCount_--) dp[i]=dp[i+1];
}
