filterCallback(void)
{
  std::list<ArPoseWithTime *>::iterator it;

  lockDevice();

  if (myMaxSecondsToKeepCurrent > 0 &&
      myCurrentBuffer.getSize() > 0)
  {

    myCurrentBuffer.beginInvalidationSweep();
    for (it = getCurrentBuffer()->begin();
	 it != getCurrentBuffer()->end();
	 ++it)
    {
      if ((*it)->getTime().secSince() >= myMaxSecondsToKeepCurrent)
	myCurrentBuffer.invalidateReading(it);
    }
    myCurrentBuffer.endInvalidationSweep();
  }


  bool doingDist = true;
  bool doingAge = true;

  if (myCumulativeBuffer.getSize() == 0)
  {
    unlockDevice();
    return;
  }

  double squaredFarDist = (myMaxDistToKeepCumulative *
			   myMaxDistToKeepCumulative);

  if (squaredFarDist < 1)
    doingDist = false;
  if (myMaxSecondsToKeepCumulative <= 0)
    doingAge = false;

  if (!doingDist && !doingAge)
  {
    unlockDevice();
    return;
  }


  myCumulativeBuffer.beginInvalidationSweep();
  for (it = getCumulativeBuffer()->begin();
       it != getCumulativeBuffer()->end();
       ++it)
  {

    if (doingDist &&
	myRobot->getPose().squaredFindDistanceTo(*(*it)) > squaredFarDist)
      myCumulativeBuffer.invalidateReading(it);
    else if (doingAge &&
	     (*it)->getTime().secSince() >= myMaxSecondsToKeepCumulative)
      myCumulativeBuffer.invalidateReading(it);
  }
  myCumulativeBuffer.endInvalidationSweep();
  unlockDevice();
}
