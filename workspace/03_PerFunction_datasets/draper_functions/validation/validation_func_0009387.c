viewschnet( Net )

  schnet_list *Net ;
{
  schwir_list *ScanWire;
  schcon_list *ScanCon;
  chain_list  *ScanChain;
  char        *RootName;

  fprintf( stdout, "\n  --> Net" );
  fprintf( stdout, "\n  NUMBER_IN   : %ld", Net->NUMBER_IN );
  fprintf( stdout, "\n  NUMBER_OUT  : %ld", Net->NUMBER_OUT );
  fprintf( stdout, "\n  FLAGS       : %lx", Net->FLAGS );

  fprintf( stdout, "\n  SOURCE_TYPE : %d", (int)Net->SOURCE_TYPE );
  fprintf( stdout, "\n  USER        : %lx", (long)Net->USER );

  fprintf( stdout, "\n  CON_NET     :" );

  for ( ScanChain  = Net->CON_NET;
        ScanChain != (chain_list *)0;
        ScanChain  = ScanChain->NEXT )
  {
    ScanCon = (schcon_list *)ScanChain->DATA;

    if ( ScanCon->ROOT_TYPE == SCH_ROOT_CON_FIG )
    {
      RootName = ((schfig_list *)ScanCon->ROOT)->NAME;
      fprintf( stdout, "\n  \t # %s\tof fig %s", ScanCon->NAME, RootName );
    }
    else
    {
      RootName = ((schbox_list *)ScanCon->ROOT)->NAME;
      fprintf( stdout, "\n  \t # %s\tof box %s", ScanCon->NAME, RootName );
    }
  }

  fprintf( stdout, "\n  WIRE :" );

  for ( ScanWire  = Net->WIRE;
        ScanWire != (schwir_list *)0;
        ScanWire  = ScanWire->NEXT )
  {
    viewschwir( ScanWire );
  }

  fprintf( stdout, "\n<-- Net" );
}
