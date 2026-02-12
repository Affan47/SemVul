cmd_directory_vector (const char *com _GL_UNUSED, const char *val, void *place)
{
  char ***pvec = (char ***)place;

  if (*val)
    {

      char **t, **seps;

      seps = sepstring (val);
      for (t = seps; t && *t; t++)
        {
          int len = strlen (*t);

          if (len > 1)
            {
              if ((*t)[len - 1] == '/')
                (*t)[len - 1] = '\0';
            }
        }
      *pvec = merge_vecs (*pvec, seps);
    }
  else
    {
      free_vec (*pvec);
      *pvec = NULL;
    }
  return true;
}
