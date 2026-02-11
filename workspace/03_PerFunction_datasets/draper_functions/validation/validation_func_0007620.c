find_interval (GeglCurvePrivate *priv,
               gdouble           u)
{
  guint len = priv->points->len;
  guint i   = 0, j = len - 1;

  while (j - i > 1)
    {
      guint k = (i + j) / 2;
      if (X (k) > u)
        j = k;
      else
        i = k;
    }

  return i;
}
