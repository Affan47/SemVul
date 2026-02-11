serialize_exif_altituderef (const GValue * value)
{
  gdouble num;

  num = g_value_get_double (value);


  if (num >= 0)
    return g_strdup ("0");
  return g_strdup ("1");
}
