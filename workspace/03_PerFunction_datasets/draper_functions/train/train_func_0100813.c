atspi_hyperlink_get_index_range (AtspiHyperlink *obj, GError **error)
{
  dbus_int32_t d_start_offset, d_end_offset;
  AtspiRange *ret = g_new (AtspiRange, 1);

  ret->start_offset = ret->end_offset = -1;

  if (!obj)
    return ret;

  _atspi_dbus_call (obj, atspi_interface_hyperlink, "GetIndexRange", error, "=>ii", &d_start_offset, &d_end_offset);

  ret->start_offset = d_start_offset;
  ret->end_offset = d_end_offset;
  return ret;
}
