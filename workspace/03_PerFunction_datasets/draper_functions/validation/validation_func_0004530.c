gegl_curve_set_point (GeglCurve      *self,
                      guint           index,
                      gdouble         x,
                      gdouble         y)
{
  GeglCurvePrivate *priv  = GEGL_CURVE_GET_PRIVATE (GEGL_CURVE (self));
  GeglCurvePoint    point;

  point.x  = x;
  point.y  = y;
  point.y2 = 1.0;

  g_assert (index < priv->points->len);
  g_array_index (priv->points, GeglCurvePoint, index) = point;

  priv->need_recalc = TRUE;
}
