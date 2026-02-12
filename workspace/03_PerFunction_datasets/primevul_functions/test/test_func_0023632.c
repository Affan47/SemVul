int cmp_longlong(void *cmp_arg,
                 in_longlong::packed_longlong *a,
                 in_longlong::packed_longlong *b)
{
  if (a->unsigned_flag != b->unsigned_flag)
  {


    if ((a->unsigned_flag && ((ulonglong) a->val) > (ulonglong) LONGLONG_MAX)
        ||
        (b->unsigned_flag && ((ulonglong) b->val) > (ulonglong) LONGLONG_MAX))
      return a->unsigned_flag ? 1 : -1;


    return cmp_longs(a->val, b->val);
  }
  if (a->unsigned_flag)
    return cmp_ulongs((ulonglong) a->val, (ulonglong) b->val);
  return cmp_longs(a->val, b->val);
}
