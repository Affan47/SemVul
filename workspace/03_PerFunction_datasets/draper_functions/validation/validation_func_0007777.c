gt_qbenchsort_permute_ulong_array (unsigned long *arr,
                                               unsigned long size)
{
  unsigned long i, j, c;

  for (i = 0; i < size; ++i)
  {
    j = gt_rand_max(size-1);
    c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
  }
}
