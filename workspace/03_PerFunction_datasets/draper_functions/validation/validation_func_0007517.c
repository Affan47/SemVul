new_cf_append(unsigned n_cfs)
{
  CFP result = (CFP) new_cf(sizeof(struct st_cf_append)
			    + (n_cfs-1) * sizeof(CF));
  if (result) {
    result->pos = 0;
    result->n_cfs = n_cfs;
  }
  return result;
}
