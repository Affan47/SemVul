gst_value_lcopy_int_range (const GValue * value, guint n_collect_values,
    GTypeCValue * collect_values, guint collect_flags)
{
  guint32 *int_range_start = collect_values[0].v_pointer;
  guint32 *int_range_end = collect_values[1].v_pointer;
  guint32 *int_range_step = collect_values[2].v_pointer;
  gint *vals = (gint *) value->data[0].v_pointer;

  if (!int_range_start)
    return g_strdup_printf ("start value location for `%s' passed as NULL",
        G_VALUE_TYPE_NAME (value));
  if (!int_range_end)
    return g_strdup_printf ("end value location for `%s' passed as NULL",
        G_VALUE_TYPE_NAME (value));
  if (!int_range_step)
    return g_strdup_printf ("step value location for `%s' passed as NULL",
        G_VALUE_TYPE_NAME (value));

  if (G_UNLIKELY (vals == NULL)) {
    return g_strdup_printf ("Uninitialised `%s' passed",
        G_VALUE_TYPE_NAME (value));
  }

  *int_range_start = INT_RANGE_MIN (value);
  *int_range_end = INT_RANGE_MAX (value);
  *int_range_step = INT_RANGE_STEP (value);

  return NULL;
}
