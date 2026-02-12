int Curl_fnmatch(void *ptr, const char *pattern, const char *string)
{
  (void)ptr;

  if(!pattern || !string) {
    return CURL_FNMATCH_FAIL;
  }
  return loop((unsigned char *)pattern, (unsigned char *)string);
}
