gt_suffixsortspace_showrange(const GtSuffixsortspace *sssp,
                                  unsigned long subbucketleft,
                                  unsigned long width)
{
  unsigned long idx;

  printf("%lu,%lu=",sssp->bucketleftidx+subbucketleft-sssp->partoffset,
                    sssp->bucketleftidx+subbucketleft+width-1-sssp->partoffset);
  for (idx=sssp->bucketleftidx+subbucketleft-sssp->partoffset;
       idx<sssp->bucketleftidx+subbucketleft+width-sssp->partoffset;
       idx++)
  {
    printf(" %lu", gt_suffixsortspace_getdirect(sssp,idx));
  }
}
