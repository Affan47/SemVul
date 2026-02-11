laserCreate(const char *laserType, int laserNumber,
				    const char *logPrefix)
{
  std::map<std::string, ArRetFunctor2<ArLaser *, int, const char *> *, ArStrCaseCmpOp>::iterator it;
  if ((it = ourLaserCreatorMap.find(laserType)) == ourLaserCreatorMap.end())
  {
    ArLog::log(ArLog::Normal, "%sCannot create a laser of type %s options are <%s>", logPrefix, laserType, laserGetTypes());
    return NULL;
  }

  return (*it).second->invokeR(laserNumber, logPrefix);
}
