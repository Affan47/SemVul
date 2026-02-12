cgiSetCookie(const char *name,
             const char *value,
             const char *path,
	     const char *domain,
	     time_t     expires,
	     int        secure)
{
  num_cookies = cupsAddOption(name, value, num_cookies, &cookies);

  printf("Set-Cookie: %s=%s;", name, value);
  if (path)
    printf(" path=%s;", path);
  if (domain)
    printf(" domain=%s;", domain);
  if (expires)
  {
    char	date[256];

    printf(" expires=%s;", httpGetDateString2(expires, date, sizeof(date)));
  }
  if (secure)
    puts(" httponly; secure;");
  else
    puts(" httponly;");
}
