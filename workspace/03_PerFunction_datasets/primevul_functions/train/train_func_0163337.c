int safe_free (void **p)
{
  free(*p);
  *p = 0;
}
