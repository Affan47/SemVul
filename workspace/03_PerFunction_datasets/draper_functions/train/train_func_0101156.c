df_readable (bool negative, uintmax_t n, char *buf,
             uintmax_t input_units, uintmax_t output_units)
{
  if (! known_value (n) && !negative)
    return "-";
  else
    {
      char *p = human_readable (negative ? -n : n, buf + negative,
                                human_output_opts, input_units, output_units);
      if (negative)
        *--p = '-';
      return p;
    }
}
