ClonePixelWands(const PixelWand **wands,
  const size_t number_wands)
{
  register ssize_t
    i;

  PixelWand
    **clone_wands;

  clone_wands=(PixelWand **) AcquireQuantumMemory((size_t) number_wands,
    sizeof(*clone_wands));
  if (clone_wands == (PixelWand **) NULL)
    ThrowWandFatalException(ResourceLimitFatalError,"MemoryAllocationFailed",
      GetExceptionMessage(errno));
  for (i=0; i < (ssize_t) number_wands; i++)
    clone_wands[i]=ClonePixelWand(wands[i]);
  return(clone_wands);
}
