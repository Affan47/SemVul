GetMagickRegistry(const ssize_t id,RegistryType *type,
  size_t *length,ExceptionInfo *exception)
{
  char
    key[MaxTextExtent];

  void
    *blob;

  *type=UndefinedRegistryType;
  *length=0;
  (void) FormatLocaleString(key,MaxTextExtent,"%.20g\n",(double) id);
  blob=(void *) GetImageRegistry(ImageRegistryType,key,exception);
  if (blob != (void *) NULL)
    return(blob);
  blob=(void *) GetImageRegistry(ImageInfoRegistryType,key,exception);
  if (blob != (void *) NULL)
    return(blob);
  return((void *) GetImageRegistry(UndefinedRegistryType,key,exception));
}
