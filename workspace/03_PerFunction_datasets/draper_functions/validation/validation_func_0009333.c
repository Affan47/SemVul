GetImageFromMagickRegistry(const char *name,long *id,
  ExceptionInfo *exception)
{
  Image
    *image;

  register RegistryInfo
    *p;

  *id=(-1);
  image=(Image *) NULL;
  LockSemaphoreInfo(registry_semaphore);
  for (p=registry_list; p != (RegistryInfo *) NULL; p=p->next)
  {
    if (p->type != ImageRegistryType)
      continue;
    if (LocaleCompare(((Image *) p->blob)->filename,name) == 0)
      {
        *id=p->id;
        image=CloneImageList((Image *) p->blob,exception);
        break;
      }
  }
  UnlockSemaphoreInfo(registry_semaphore);
  if (image == (Image *) NULL)
    ThrowException(exception,RegistryError,UnableToLocateImage,name);
  return (image);
}
