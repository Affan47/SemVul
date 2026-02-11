checkLockTime()
{

  if (ourLockWarningMS > 0 && myLockStarted &&
        myLockStarted->mSecSince() >= ourLockWarningMS)
    ArLog::logNoLock(
   	  ArLog::Normal,
   	  "LockWarning: locking '%s' from thread '%s' %d pid %d took %.3f sec",
      myLogName.c_str(), ArThread::getThisThreadName(),
   	  ArThread::getThisThread(),
#ifdef WIN32
	  0,
#else
	  getpid(),
#endif
   	  myLockStarted->mSecSince() / 1000.0);

}
