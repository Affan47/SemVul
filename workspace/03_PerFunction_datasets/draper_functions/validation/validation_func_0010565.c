viewrtlport( Port )

  rtlport_list *Port;
{
  fprintf( stdout, "\n--> Port" );

  fprintf( stdout, "\n\t\tVEX_ATOM : " );
  viewvexexprbound( Port->VEX_ATOM );

  if ( Port->DIR >= RTL_MAX_DIR_TYPE )
  {
    fprintf( stdout, "\n\t\tDIR   : %d", (int)Port->DIR  );
  }
  else
  {
    fprintf( stdout, "\n\t\tDIR   : %s", RTL_DIR_TYPE[ Port->DIR ] );
  }

  if ( Port->BASE >= VEX_MAX_TYPE )
  {
    fprintf( stdout, "\n\t\tBASE  : %d", Port->BASE );
  }
  else
  {
    fprintf( stdout, "\n\t\tBASE  : %s", VEX_TYPE_NAME[ Port->BASE ] );
  }

  fprintf( stdout, "\n\t\tFLAGS : %lx", Port->FLAGS );
  fprintf( stdout, "\n\t\tUSER  : %lx", (long)Port->USER );
  fprintf( stdout, "\n<-- Port" );
}
