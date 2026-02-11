open_repo_file (const char *filename)
{
  const char *p;
  const char *s = get_base_filename (filename);

  if (s == NULL)
    return;

  p = lbasename (s);
  p = strrchr (p, '.');
  if (! p)
    p = s + strlen (s);

  repo_name = xmalloc (p - s + 5);
  memcpy (repo_name, s, p - s);
  memcpy (repo_name + (p - s), ".rpo", 5);

  repo_file = fopen (repo_name, "r");
}
