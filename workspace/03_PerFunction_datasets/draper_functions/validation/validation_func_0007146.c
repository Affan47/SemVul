MochaSyfSynthFsmInit( FsmFigure )

  fsmfig_list *FsmFigure;
{
  mochasyfinfo     *MochaSyfInfo;
  char              Buffer[ 25 ];
  mochasyfregstate *RegArray;
  long              RegMax;
  long              Index;

  MochaSyfInfo = MOCHA_SYF_INFO( FsmFigure );

  RegMax   = MochaSyfInfo->NUMBER_BIT;
  RegArray = (mochasyfregstate  *)autallocblock( sizeof( mochasyfregstate ) * RegMax );

  for ( Index = 0; Index < RegMax; Index++ )
  {
    sprintf( Buffer, "%s %ld", MochaSyfInfo->CURRENT_STATE, Index );
    RegArray[ Index ].NAME_OUT = namealloc( Buffer );
    sprintf( Buffer, "%s %ld", MochaSyfInfo->NEXT_STATE, Index );
    RegArray[ Index ].NAME_IN = namealloc( Buffer );
    RegArray[ Index ].NAME_MASTER = RegArray[ Index ].NAME_OUT;
  }

  MochaSyfInfo->REG_ARRAY  = RegArray;
  MochaSyfInfo->NUMBER_REG = RegMax;
}
