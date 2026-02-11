SetScreenUpdater( PG_ScreenUpdater* screenUpdater )
{
   if ( screenUpdater != NULL )
      my_ScreenUpdater = screenUpdater;
   else
      my_ScreenUpdater = &defaultScreenUpdater;
}
