vtkWrap_IsConstructor(ClassInfo *c, FunctionInfo *f)

{
  size_t i, m;
  const char *cp = c->Name;

  if (cp && f->Name && !vtkWrap_IsDestructor(c, f))
    {

    m = vtkParse_UnscopedNameLength(cp);
    while (cp[m] == ':' && cp[m+1] == ':')
      {
      cp += m + 2;
      m = vtkParse_UnscopedNameLength(cp);
      }
    for (i = 0; i < m; i++)
      {
      if (cp[i] == '<')
        {
        break;
        }
      }

    return (i == strlen(f->Name) && strncmp(cp, f->Name, i) == 0);
    }

  return 0;
}
