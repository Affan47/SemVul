static void go_sleep(long ms)
{
#ifdef HAVE_POLL_FINE

  poll((void *)0, 0, (int)ms);
#else


#ifdef WIN32

  Sleep(ms);
#elif defined(MSDOS)
  delay(ms);
#else

  struct timeval timeout;

  timeout.tv_sec = ms/1000;
  ms = ms%1000;
  timeout.tv_usec = ms * 1000;

  select(0, NULL,  NULL, NULL, &timeout);
#endif

#endif
}
