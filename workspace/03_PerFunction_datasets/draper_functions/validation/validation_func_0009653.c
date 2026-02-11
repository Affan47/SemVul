operator--()
{
  unsigned int len=_pImpl->length();

  if (len>0)
    {
      unsigned int *pData=data();
      _pImpl->prepareToChangeWithoutCopy();

      if (pData==data())
	{
	  for (unsigned int i=0; i<len; i++)
	    {
	      --pData[i];
	    }
	}
      else
	{

	  unsigned int *pNewData=data();

	  while (len--)
	    {
	      *pNewData++ = *pData++ -1;
	    }
	}

      changed();
    }

  return *this;
}
