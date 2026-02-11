numberOfVariablesInUseConsecutive()const
{
  int ret=0;

  for(TermMap::const_iterator i=terms.begin();i!=terms.end();i++)
    {
      int a=i->first.exponent.indexOfLargestNonzeroEntry()+1;
      if(a>ret)ret=a;
    }

  return ret;
}
