encdesc_digits_per_value(unsigned long value,
                                         unsigned long base)
{
  if (value > 0) {
    double log_val, log_base;
    log_val = log((double) value);
    log_base = log((double) base);
    return (unsigned) (floor(log_val / log_base )) + 1U;
  }
  else
    return 1U;
}
