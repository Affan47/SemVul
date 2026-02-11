direct_signals_block_all( void )
{
     sigset_t signals;

     D_DEBUG_AT( Direct_Signals, "Blocking all signals from now on!\n" );

     sigfillset( &signals );

     if (pthread_sigmask( SIG_BLOCK, &signals, NULL ))
          D_PERROR( "Direct/Signals: Setting signal mask failed!\n" );
}
