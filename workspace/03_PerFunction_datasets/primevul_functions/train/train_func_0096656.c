static void prepare()
  {
    using namespace XrdCl;
    Log         *log         = DefaultEnv::GetLog();
    Env         *env         = DefaultEnv::GetEnv();
    ForkHandler *forkHandler = DefaultEnv::GetForkHandler();

    log->Debug( UtilityMsg, "In the prepare fork handler for process %d",
                getpid() );


    int runForkHandler = DefaultRunForkHandler;
    env->GetInt( "RunForkHandler", runForkHandler );
    if( runForkHandler )
      forkHandler->Prepare();
    env->WriteLock();
  }
