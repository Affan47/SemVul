new_string (char *t, ...)
{
  va_list vl;
  char *q, *z;
  int len = 0;
  va_start (vl, t);
  q = t;
  while (q != NO_TEXT) {
    len += (int) strlen (q);
    q = va_arg (vl, char *);
  }
  va_end (vl);
  len ++;
  z = (char *) get_heap_space ((size_t) len);
  z[0] = NULL_CHAR;
  q = t;
  va_start (vl, t);
  while (q != NO_TEXT) {
    bufcat (z, q, len);
    q = va_arg (vl, char *);
  }
  va_end (vl);
  return (z);
}
