char *get_next_file()
{
  char *ret;
  DWORD dwWaitResult;
  if (!queue)
    return NULL;
  if (qptr >= qsize)
    return NULL;

  dwWaitResult = WaitForSingleObject(qmutex,
                                     INFINITE);
  switch (dwWaitResult)
  {

  case WAIT_OBJECT_0:
    ret = queue[qptr++];
    ReleaseMutex(qmutex);
    break;
  case WAIT_ABANDONED:
    return NULL;
  };
  return ret;
}
