gt_rmq_log2fast(unsigned long v)
{
  unsigned long c = 0;
  register unsigned long t, tt;

  if ((tt = v >> 16))
  {
    c = (t = v >> 24) ? 24UL + (unsigned long) gt_rmq_LogTable256[t]
                      : 16 + (unsigned long) gt_rmq_LogTable256[tt & 0xFF];
  } else
  {
    c = (t = v >> 8) ? 8UL + (unsigned long) gt_rmq_LogTable256[t]
                     : (unsigned long) gt_rmq_LogTable256[v];
  }
  return (unsigned long) c;
}
