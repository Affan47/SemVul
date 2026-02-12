__gst_date_time_compare (const GstDateTime * dt1, const GstDateTime * dt2)
{
  gint64 diff;


  if (dt1->fields != dt2->fields)
    return GST_VALUE_UNORDERED;


  diff =
      g_date_time_to_unix (dt1->datetime) - g_date_time_to_unix (dt2->datetime);
  if (diff < 0)
    return GST_VALUE_LESS_THAN;
  else if (diff > 0)
    return GST_VALUE_GREATER_THAN;
  else
    return GST_VALUE_EQUAL;
}
