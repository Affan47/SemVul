file_rlookup(const char *filename)
{
  int		i;
  cache_t	*wc;


  for (i = web_files, wc = web_cache; i > 0; i --, wc ++)
  {
    if (!strcmp(wc->name, filename))
    {
      if (!strncmp(wc->url, "data:", 5))
        return ("data URL");
      else
        return (wc->url);
    }
  }

  return (filename);
}
