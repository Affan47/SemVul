cgiGetCookie(const char *name)
{
  return (cupsGetOption(name, num_cookies, cookies));
}
