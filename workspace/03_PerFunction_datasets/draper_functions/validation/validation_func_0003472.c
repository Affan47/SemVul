preview_event_configure (GtkWidget         *widget,
                         GdkEventConfigure *event,
                         gpointer           user_data)
{
  gboolean retval;
  GSCHEM_TOPLEVEL *preview_w_current = PREVIEW (widget)->preview_w_current;
  PAGE     *preview_page = preview_w_current->toplevel->page_current;

  retval = x_event_configure (widget, event, preview_w_current);
  if (preview_page != NULL) {
    a_zoom_extents(preview_w_current, s_page_objects (preview_page), 0);
  }
  return retval;
}
