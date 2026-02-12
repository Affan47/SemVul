static void cleanarg(char *str)
{
#ifdef HAVE_WRITABLE_ARGV


  if (str) {
    size_t len = strlen(str);
    memset(str, ' ', len);
  }
#else
  (void)str;
#endif
}
