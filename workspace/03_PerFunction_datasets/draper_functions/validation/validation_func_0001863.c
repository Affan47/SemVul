create(void (*entry)(void*), void *arg)
{
  if (xentry || xarg)
    return -1;
  xentry = entry;
  xarg = arg;
#ifdef DCETHREADS
  int ret = pthread_create(&hthr, pthread_attr_default, GThread::start, (void*)this);
  if (ret >= 0)
    pthread_detach(hthr);
#else
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  int ret = pthread_create(&hthr, &attr, start, (void*)this);
  pthread_attr_destroy(&attr);
#endif
  return ret;
}
