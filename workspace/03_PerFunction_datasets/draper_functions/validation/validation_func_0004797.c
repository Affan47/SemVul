set_fast_math_flags (struct gcc_options *opts, int set)
{
  if (!opts->frontend_set_flag_unsafe_math_optimizations)
    {
      opts->x_flag_unsafe_math_optimizations = set;
      set_unsafe_math_optimizations_flags (opts, set);
    }
  if (!opts->frontend_set_flag_finite_math_only)
    opts->x_flag_finite_math_only = set;
  if (!opts->frontend_set_flag_errno_math)
    opts->x_flag_errno_math = !set;
  if (set)
    {
      if (!opts->frontend_set_flag_signaling_nans)
	opts->x_flag_signaling_nans = 0;
      if (!opts->frontend_set_flag_rounding_math)
	opts->x_flag_rounding_math = 0;
      if (!opts->frontend_set_flag_cx_limited_range)
	opts->x_flag_cx_limited_range = 1;
    }
}
