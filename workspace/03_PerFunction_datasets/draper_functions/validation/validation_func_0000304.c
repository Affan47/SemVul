getCurrentTime(bool Start) {
  TimeRecord Result;
  sys::TimeValue now(0,0), user(0,0), sys(0,0);

  if (Start) {
    Result.MemUsed = getMemUsage();
    sys::Process::GetTimeUsage(now, user, sys);
  } else {
    sys::Process::GetTimeUsage(now, user, sys);
    Result.MemUsed = getMemUsage();
  }

  Result.WallTime   =  now.seconds() +  now.microseconds() / 1000000.0;
  Result.UserTime   = user.seconds() + user.microseconds() / 1000000.0;
  Result.SystemTime =  sys.seconds() +  sys.microseconds() / 1000000.0;
  return Result;
}
