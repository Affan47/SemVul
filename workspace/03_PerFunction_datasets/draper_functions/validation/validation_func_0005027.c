ira_conflict_vector_profitable_p (ira_object_t obj, int num)
{
  int nw;
  int max = OBJECT_MAX (obj);
  int min = OBJECT_MIN (obj);

  if (max < min)


    return false;

  nw = (max - min + IRA_INT_BITS) / IRA_INT_BITS;
  return (2 * sizeof (ira_object_t) * (num + 1)
	  < 3 * nw * sizeof (IRA_INT_TYPE));
}
