vtkHashString(const char* s)
{
  unsigned long h = 0;
  for ( ; *s; ++s)
    {
    h = 5*h + *s;
    }
  return size_t(h);
}
