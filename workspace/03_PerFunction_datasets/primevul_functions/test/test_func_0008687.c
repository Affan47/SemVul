cupsdInitCerts(void)
{
#ifndef HAVE_ARC4RANDOM
  cups_file_t	*fp;


  if ((fp = cupsFileOpen("/dev/urandom", "rb")) == NULL)
  {
    struct timeval tod;


    gettimeofday(&tod, NULL);

    CUPS_SRAND((unsigned)(tod.tv_sec + tod.tv_usec));
  }
  else
  {
    unsigned	seed;


    seed = (unsigned)cupsFileGetChar(fp);
    seed = (seed << 8) | (unsigned)cupsFileGetChar(fp);
    seed = (seed << 8) | (unsigned)cupsFileGetChar(fp);
    CUPS_SRAND((seed << 8) | (unsigned)cupsFileGetChar(fp));

    cupsFileClose(fp);
  }
#endif


  if (!RunUser)
    cupsdAddCert(0, "root", cupsdDefaultAuthType());
}
