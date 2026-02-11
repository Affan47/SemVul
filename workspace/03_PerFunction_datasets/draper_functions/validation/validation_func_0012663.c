gethostname () const
{
  if (sin_addr.s_addr == htonl(INADDR_ANY)) {
    static char hostname[64];
    if (::gethostname(hostname, 63) == -1) return "";
    return hostname;
  }

  hostent* hp = gethostbyaddr((const char*) &sin_addr,
                  sizeof(sin_addr),
                  family());
  if (hp == 0) return "";
  if (hp->h_name) return hp->h_name;
  return "";
}
