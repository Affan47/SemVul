__fslash(char *a) {
  int i;

  for(i = 0; a[i] != 0; i++)
    if (a[i] == '\\')
      a[i] = '/';
  return a;
}
