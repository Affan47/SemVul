cpio_safer_name_suffix (char *name, bool link_target, bool absolute_names,
			bool strip_leading_dots)
{
  char *p = safer_name_suffix (name, link_target, absolute_names);
  if (strip_leading_dots && strcmp (p, "./"))

    while (*p == '.' && *(p + 1) == '/')
      {
	++p;
	while (*p == '/')
	  ++p;
      }
  if (p != name)


    memmove (name, p, (size_t)(strlen (p) + 1));
}
