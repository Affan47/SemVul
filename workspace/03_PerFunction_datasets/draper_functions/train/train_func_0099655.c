FvhFbhGetStack( Name )

  char *Name;
{
  chain_list *ScanChain;
  int         Index;

  Index = 0;

  for ( ScanChain  = FvhDefaultStackName;
        ScanChain != (chain_list *)0;
        ScanChain  = ScanChain->NEXT )
  {
    if ( ScanChain->DATA == (void *)Name )
    {
      return( Index );
    }

    Index = Index + 1;
  }

  return( -1 );
}
