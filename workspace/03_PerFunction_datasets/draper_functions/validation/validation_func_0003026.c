unlock()
{
  if (myLog)
    ArLog::logNoLock(ArLog::Terse,
		     "Unlocking '%s' from thread '%s' %d pid %d",
		     myLogName.c_str(),
		     ArThread::getThisThreadName(),
		     ArThread::getThisThread(), getpid());

  if(ourUnlockWarningMS > 0) checkUnlockTime();

  if (myFailedInit)
  {
    ArLog::logNoLock(ArLog::Terse, "ArMutex::unlock: Initialization of mutex '%s' from thread '%s' %d pid %d failed, failed unlock",
		     myLogName.c_str(), ArThread::getThisThreadName(),
		     ArThread::getThisThread(), getpid());
    return(STATUS_FAILED_INIT);
  }

  int ret;
  if ((ret = pthread_mutex_unlock(&myMutex)) != 0)
  {
    if (ret == EPERM)
    {
      ArLog::logNoLock(ArLog::Terse, "ArMutex::unlock: Trying to unlock a mutex ('%s') which this thread ('%s' %d pid %d) does not own",
		       myLogName.c_str(), ArThread::getThisThreadName(),
		       ArThread::getThisThread(), getpid());
      return(STATUS_ALREADY_LOCKED);
    }
    else
    {
      ArLog::logNoLock(ArLog::Terse, "ArMutex::unlock: Failed to unlock mutex ('%s') from thread ('%s' %d pid %d) due to an unknown error",
		       myLogName.c_str(), ArThread::getThisThreadName(),
		       ArThread::getThisThread(), getpid());
      return(STATUS_FAILED);
    }
  }
  if (myNonRecursive)
    myWasAlreadyLocked = false;
  return(0);
}
