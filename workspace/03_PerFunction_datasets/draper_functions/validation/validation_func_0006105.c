resume(bool nocontinue)
{
  QMutexLocker locker(&d->mutex);
  if (!d->pauseLoop || !d->rflag)
    return false;
  if (nocontinue)
    d->pauseLoop->exit(1);
  else
    d->pauseLoop->exit(0);
  return true;
}
