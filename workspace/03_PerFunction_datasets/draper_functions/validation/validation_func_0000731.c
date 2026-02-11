ChangeLocation (void)
{
  if (setLocBusy) return FALSE;
  char *lstr = (char *) gtk_entry_get_text (GTK_ENTRY (location));
  double lat, lon;
  while (*lstr != '?' && *lstr != '\0') lstr++;
  if (sscanf (lstr, "?lat=%lf&lon=%lf&zoom=%d", &lat, &lon, &zoom) == 3) {
    clat = Latitude (lat);
    clon = Longitude (lon);
    zoom = 0xffffffff >> (zoom - 1);
    gtk_widget_queue_clear (draw);
  }
  return FALSE;
}
