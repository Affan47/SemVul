url_skip_credentials (const char *url)
{


  const char *p = (const char *)strpbrk (url, "@/?#;");
  if (!p || *p != '@')
    return url;
  return p + 1;
}
