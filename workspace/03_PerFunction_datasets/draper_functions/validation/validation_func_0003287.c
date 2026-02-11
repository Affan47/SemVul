atspi_text_get_range_extents (AtspiText *obj,
				gint start_offset,
				gint end_offset,
				AtspiCoordType type,
				GError **error)
{
  dbus_int32_t d_start_offset = start_offset, d_end_offset = end_offset;
  dbus_uint32_t d_type = type;
  dbus_int32_t d_x, d_y, d_width, d_height;
  AtspiRect ret;

  ret.x = ret.y = ret.width = ret.height = -1;

  if (obj == NULL)
    return atspi_rect_copy (&ret);

  _atspi_dbus_call (obj, atspi_interface_text, "GetRangeExtents", error, "iiu=>iiii", d_start_offset, d_end_offset, d_type, &d_x, &d_y, &d_width, &d_height);

  ret.x = d_x;
  ret.y = d_y;
  ret.width = d_width;
  ret.height = d_height;
  return atspi_rect_copy (&ret);
}
