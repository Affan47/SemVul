static bool bad_domain(const char *domain)
{
  if(strcasecompare(domain, "localhost"))
    return FALSE;
  else {

    char *dot = strchr(domain, '.');
    if(dot)
      return dot[1] ? FALSE : TRUE;
  }
  return TRUE;
}
