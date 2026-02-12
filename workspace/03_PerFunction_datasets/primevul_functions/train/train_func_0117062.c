MagickExport double *StringToArrayOfDoubles(const char *string,ssize_t *count,
  ExceptionInfo *exception)
{
  char
    *q;

  const char
    *p;

  double
    *array;

  register ssize_t
    i;


  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  *count=0;
  if (string == (char *) NULL)
    return((double *) NULL);
  i=0;
  p=string;
  while (*p != '\0')
  {
    (void) StringToDouble(p,&q);
    if (p == q)
      return((double *) NULL);
    p=q;
    i++;
    while (isspace((int) ((unsigned char) *p)) != 0)
      p++;
    if (*p == ',')
      p++;
    while (isspace((int) ((unsigned char) *p)) != 0)
      p++;
  }


  *count=i;
  array=(double *) AcquireQuantumMemory((size_t) i,sizeof(*array));
  if (array == (double *) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'","");
      return((double *) NULL);
    }


  i=0;
  p=string;
  while ((*p != '\0') && (i < *count))
  {
    array[i++]=StringToDouble(p,&q);
    p=q;
    while ((isspace((int) ((unsigned char) *p)) != 0) || (*p == ','))
      p++;
  }
  return(array);
}
