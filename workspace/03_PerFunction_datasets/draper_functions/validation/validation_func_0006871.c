performSnapShot(int currentTime)
{
  if (isCheckPoint(currentTime))
  {
    issueSnapShotCmd(currentTime);
  }
}
