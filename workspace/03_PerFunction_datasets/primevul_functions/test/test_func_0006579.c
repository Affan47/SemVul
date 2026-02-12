suffix_requires_dir_check (char const *end)
{

  while (ISSLASH (*end))
    {

      do
        end++;
      while (ISSLASH (*end));

      switch (*end++)
        {
        default: return false;
        case '\0': return true;
        case '.': break;
        }

      if (!*end || (*end == '.' && (!end[1] || ISSLASH (end[1]))))
        return true;
    }

  return false;
}
