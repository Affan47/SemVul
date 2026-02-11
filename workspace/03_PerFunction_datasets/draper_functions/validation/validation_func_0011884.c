postRestart()
{
  isRestarting = true;
  _originalToCurrentShmids.clear();

  for (ShmIterator i = _shm.begin(); i != _shm.end(); ++i) {
    ShmSegment& shmObj = i->second;
    if (shmObj.isCkptLeader()) {
      JTRACE("Writing ShmidMap to file")(shmObj.originalShmid());
      _originalToCurrentShmids[shmObj.originalShmid()] = shmObj.currentShmid();
    }
  }
  if (_originalToCurrentShmids.size() > 0) {
    writeShmidMapsToFile(PROTECTED_SHMIDLIST_FD);
  }
}
