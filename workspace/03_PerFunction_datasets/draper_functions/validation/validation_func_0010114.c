champlain_map_source_get_longitude (ChamplainMapSource *map_source,
    guint zoom_level,
    gdouble x)
{
  gdouble longitude;

  g_return_val_if_fail (CHAMPLAIN_IS_MAP_SOURCE (map_source), 0.0);

  gdouble dx = (gdouble) x / champlain_map_source_get_tile_size (map_source);
  longitude = dx / pow (2.0, zoom_level) * 360.0 - 180.0;

  return CLAMP (longitude, CHAMPLAIN_MIN_LONGITUDE, CHAMPLAIN_MAX_LONGITUDE);
}
