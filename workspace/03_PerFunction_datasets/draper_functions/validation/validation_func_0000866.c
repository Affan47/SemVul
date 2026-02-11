_realpath (const char *path)
{
#ifndef _WIN32
  char buffer[G_PATH_LENGTH];

  return realpath (path, buffer) ? g_strdup (buffer) : NULL;
#else


#ifndef USE_WINDOWS
  extern __stdcall GetFullPathNameA(const char*, int, char*, char**);
#endif
  char *buffer;
  char dummy;
  int rc, len;

  rc = GetFullPathNameA (path, 1, &dummy, NULL);
  if (rc == 0)
    {

      return g_strdup (path);
    }

  len = rc + 1;
  buffer = g_malloc (len);

  rc = GetFullPathNameA (path, len, buffer, NULL);
  if (rc == 0 || rc > len)
    {

      g_free (buffer);
      return g_strdup (path);
    }
  return buffer;
#endif
}
