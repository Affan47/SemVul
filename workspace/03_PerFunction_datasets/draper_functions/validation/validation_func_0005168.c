check_range (const gchar * str, gchar ** tmp, gint * range)
{
  glong range_val;

  range_val = strtol (str, tmp, 10);
  if (range_val >= G_MININT && range_val <= G_MAXINT) {
    *range = range_val;
    return TRUE;
  } else {
    return FALSE;
  }
}
