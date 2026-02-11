ResetRadonCells(RadonInfo *radon_info)
{
  register ssize_t
    x;

  ssize_t
    count,
    y;

  unsigned short
    value;

  if (radon_info->type != DiskCache)
    {
      (void) ResetMagickMemory(radon_info->cells,0,(size_t) radon_info->length);
      return(MagickTrue);
    }
  value=0;
  (void) lseek(radon_info->file,0,SEEK_SET);
  for (y=0; y < (ssize_t) radon_info->height; y++)
  {
    for (x=0; x < (ssize_t) radon_info->width; x++)
    {
      count=write(radon_info->file,&value,sizeof(*radon_info->cells));
      if (count != (ssize_t) sizeof(*radon_info->cells))
        break;
    }
    if (x < (ssize_t) radon_info->width)
      break;
  }
  return(y < (ssize_t) radon_info->height ? MagickFalse : MagickTrue);
}
