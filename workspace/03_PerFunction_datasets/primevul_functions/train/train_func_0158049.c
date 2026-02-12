void WlmActivityManager::CleanChildren()


{

#ifdef HAVE_WAITPID
  int options = WNOHANG;
  int stat_loc;
  int child=1;

  while( child > 0 )
  {

    child = (int)(waitpid(-1, &stat_loc, options));
    if( child == 0 )
    {

    }
    else if( child < 0 )
    {
      if( errno == ECHILD )
      {

      }
      else
      {
        DCMWLM_WARN("WlmActivityManager::CleanChildren: Wait for child failed");
      }
    }
    else if( child > 0 )
    {

      DCMWLM_INFO("Cleaned up after child (" << child << ")");


      RemoveProcessFromTable( child );
    }
  }

#elif HAVE_WAIT3
#if defined(__NeXT__)

  union wait status;
#else
  int status;
#endif
  int options = WNOHANG;
  struct rusage rusage;
  int child = 1;

  while( child > 0 )
  {

    child = wait3( &status, options, &rusage );
    if( child < 0 )
    {
      if( errno == ECHILD )
      {

      }
      else
      {
        DCMWLM_WARN("WlmActivityManager::CleanChildren: Wait for child failed");
      }
    }
    else if( child > 0 )
    {

      DCMWLM_INFO("Cleaned up after child (" << child << ")");


      RemoveProcessFromTable( child );
    }
  }
#else


  DCMWLM_WARN("WlmActivityManager::CleanChildren: Cannot wait for child processes");
#endif
}
