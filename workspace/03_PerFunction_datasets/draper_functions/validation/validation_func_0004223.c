gemini()
{
#if !defined(DOS)

  int  ckptFunCallPath = ckptTuple . ckptAttribute ;

  if ( normalRun == checkpointStatus )
    funCallPath = fCP_gem_ ;

#endif

  continue_ = go;
  while (continue_ != quit) {
#if !defined(DOS)

    if ( ( checkpointedRun == checkpointStatus ) &&
         ( iterationLocation == ckptTuple . ckptLocation ) )
      recoverCheckpoint ( NULL ) ;
    else
    {
      if ( checkpointedRun == checkpointStatus )
      {

        if ( fCP_gem_init == ckptFunCallPath )
          goto FunRecover2 ;
        else if ( ( fCP_gem_iter_st_first == ckptFunCallPath ) ||
                  ( fCP_gem_iter_st_decr == ckptFunCallPath ) ||
                  ( fCP_gem_iter_st_incr == ckptFunCallPath ) ||
                  ( fCP_gem_iter_gcen1 == ckptFunCallPath ) ||
                  ( fCP_gem_iter_gcen2 == ckptFunCallPath ) ||
                  ( fCP_gem_iter_gfor == ckptFunCallPath ) )
          goto FunRecover34567 ;
        else if ( fCP_gem_gfor == ckptFunCallPath )
          goto FunRecover8 ;
      }
    FunRecover2:
#endif
      initilink();
#if !defined(DOS)
      funCallPath = fCP_gem_ ;
    FunRecover8:
#endif
      isw = 0;
      gforward();
#if !defined(DOS)
      funCallPath = fCP_gem_ ;
    }
#endif

    continue_ = go;
#if !defined(DOS)
  FunRecover34567:
#endif
    iterate();
#if !defined(DOS)
    funCallPath = fCP_gem_ ;
#endif
  }
  if (ivar == 1)
    inib();
}
