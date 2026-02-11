scm_merge_list_step (SCM * seq, scm_t_trampoline_2 cmp, SCM less, long n)
{
  SCM a, b;

  if (n > 2)
    {
      long mid = n / 2;
      SCM_TICK;
      a = scm_merge_list_step (seq, cmp, less, mid);
      b = scm_merge_list_step (seq, cmp, less, n - mid);
      return scm_merge_list_x (a, b, mid, n - mid, cmp, less);
    }
  else if (n == 2)
    {
      SCM p = *seq;
      SCM rest = SCM_CDR (*seq);
      SCM x = SCM_CAR (*seq);
      SCM y = SCM_CAR (SCM_CDR (*seq));
      *seq = SCM_CDR (rest);
      SCM_SETCDR (rest, SCM_EOL);
      if (scm_is_true ((*cmp) (less, y, x)))
	{
	  SCM_SETCAR (p, y);
	  SCM_SETCAR (rest, x);
	}
      return p;
    }
  else if (n == 1)
    {
      SCM p = *seq;
      *seq = SCM_CDR (p);
      SCM_SETCDR (p, SCM_EOL);
      return p;
    }
  else
    return SCM_EOL;
}
