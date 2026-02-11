gst_value_subtract_fraction_range_fraction_range (GValue * dest,
    const GValue * minuend, const GValue * subtrahend)
{


  const GValue *min1 = gst_value_get_fraction_range_min (minuend);
  const GValue *max2 = gst_value_get_fraction_range_max (minuend);
  const GValue *max1 = gst_value_get_fraction_range_min (subtrahend);
  const GValue *min2 = gst_value_get_fraction_range_max (subtrahend);
  gint cmp1, cmp2;
  GValue v1 = { 0, };
  GValue v2 = { 0, };
  GValue *pv1, *pv2;
  GstValueCompareFunc compare;

  g_return_val_if_fail (min1 != NULL && max1 != NULL, FALSE);
  g_return_val_if_fail (min2 != NULL && max2 != NULL, FALSE);

  compare = gst_value_get_compare_func (min1);
  g_return_val_if_fail (compare, FALSE);

  cmp1 = gst_value_compare_with_func (max2, max1, compare);
  g_return_val_if_fail (cmp1 != GST_VALUE_UNORDERED, FALSE);
  if (cmp1 == GST_VALUE_LESS_THAN)
    max1 = max2;
  cmp1 = gst_value_compare_with_func (min1, min2, compare);
  g_return_val_if_fail (cmp1 != GST_VALUE_UNORDERED, FALSE);
  if (cmp1 == GST_VALUE_GREATER_THAN)
    min2 = min1;

  cmp1 = gst_value_compare_with_func (min1, max1, compare);
  cmp2 = gst_value_compare_with_func (min2, max2, compare);

  if (cmp1 == GST_VALUE_LESS_THAN && cmp2 == GST_VALUE_LESS_THAN) {
    pv1 = &v1;
    pv2 = &v2;
  } else if (cmp1 == GST_VALUE_LESS_THAN) {
    pv1 = dest;
    pv2 = NULL;
  } else if (cmp2 == GST_VALUE_LESS_THAN) {
    pv1 = NULL;
    pv2 = dest;
  } else {
    return FALSE;
  }

  if (!dest)
    return TRUE;

  if (cmp1 == GST_VALUE_LESS_THAN) {
    g_value_init (pv1, GST_TYPE_FRACTION_RANGE);
    gst_value_set_fraction_range (pv1, min1, max1);
  }
  if (cmp2 == GST_VALUE_LESS_THAN) {
    g_value_init (pv2, GST_TYPE_FRACTION_RANGE);
    gst_value_set_fraction_range (pv2, min2, max2);
  }

  if (cmp1 == GST_VALUE_LESS_THAN && cmp2 == GST_VALUE_LESS_THAN) {
    gst_value_list_concat (dest, pv1, pv2);
    g_value_unset (pv1);
    g_value_unset (pv2);
  }
  return TRUE;
}
