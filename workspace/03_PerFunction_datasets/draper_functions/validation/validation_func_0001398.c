_compare_tor_version_str_ptr(const void **_a, const void **_b)
{
  const char *a = *_a, *b = *_b;
  int ca, cb;
  tor_version_t va, vb;
  ca = tor_version_parse(a, &va);
  cb = tor_version_parse(b, &vb);

  if (!ca && !cb)
    return tor_version_compare(&va,&vb);

  if (!ca && cb)
    return -1;
  if (ca && !cb)
    return 1;


  return strcmp(a,b);
}
