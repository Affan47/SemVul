mx_adjustment_interpolate_relative (MxAdjustment *adjustment,
                                    gdouble       offset,
                                    guint         duration,
                                    gulong        mode)
{
  MxAdjustmentPrivate *priv = adjustment->priv;

  if (priv->interpolation)
    offset += priv->new_position;
  else
    offset += priv->value;

  mx_adjustment_interpolate (adjustment,
                             offset,
                             duration,
                             mode);
}
