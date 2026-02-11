gt_tyrindex_check(GT_UNUSED const Tyrindex *tyrindex)
{
#ifndef NDEBUG
  GtUchar *mercodeptr;
  const GtUchar *result;
  unsigned long position;
  GT_UNUSED unsigned long previousposition = 0;

  for (mercodeptr = tyrindex->mertable;
       mercodeptr <= tyrindex->lastmer;
       mercodeptr += tyrindex->merbytes)
  {
    result = gt_tyrindex_binmersearch(tyrindex,0,mercodeptr,
                                   tyrindex->mertable,
                                   tyrindex->lastmer);
    gt_assert(result != NULL);
    if ((result - tyrindex->mertable) % tyrindex->merbytes != 0)
    {
      fprintf(stderr,"result is not multiple of %lu\n",tyrindex->merbytes);
      exit(GT_EXIT_PROGRAMMING_ERROR);
    }
    position = (unsigned long) (result-tyrindex->mertable)/
                               tyrindex->merbytes;
    if (position > 0 && previousposition + 1 != position)
    {
      fprintf(stderr,"position %lu is not increasing\n",position);
      exit(GT_EXIT_PROGRAMMING_ERROR);
    }
    previousposition = position;
  }
#endif
}
