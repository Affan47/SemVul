void rfbDecrClientRef(rfbClientPtr cl)
{
  LOCK(cl->refCountMutex);
  cl->refCount--;
  if(cl->refCount<=0)
    TSIGNAL(cl->deleteCond);
  UNLOCK(cl->refCountMutex);
}
