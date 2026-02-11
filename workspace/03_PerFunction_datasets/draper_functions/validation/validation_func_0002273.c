precompute_good_suffix_shift (char *query, int querylen) {
  int *good_suffix_shift;
  int i, j, *suffix;

  good_suffix_shift = (int *) CALLOC(querylen,sizeof(int));
  suffix = precompute_suffix(query,querylen);

  for (i = 0; i < querylen; i++) {
    good_suffix_shift[i] = querylen;
  }
  j = 0;
  for (i = querylen - 1; i >= -1; i--) {
    if (i == -1 || suffix[i] == i + 1) {
      for ( ; j < querylen - 1 - i; j++) {
	if (good_suffix_shift[j] == querylen) {
	  good_suffix_shift[j] = querylen - 1 - i;
	}
      }
    }
  }
  for (i = 0; i <= querylen - 2; i++) {
    good_suffix_shift[querylen - 1 - suffix[i]] = querylen - 1 - i;
  }

  FREE(suffix);
  return good_suffix_shift;
}
