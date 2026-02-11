gst_rsvg_overlay_set_svg_data (GstRsvgOverlay * overlay, const gchar * data,
    gboolean consider_as_filename)
{
  GstBaseTransform *btrans = GST_BASE_TRANSFORM (overlay);
  gsize size;
  GError *error = NULL;

  if (overlay->handle) {
    g_object_unref (overlay->handle);
    overlay->handle = NULL;
    gst_base_transform_set_passthrough (btrans, TRUE);
  }


  if (data) {
    size = strlen (data);
    if (size) {

      if (consider_as_filename)
        overlay->handle = rsvg_handle_new_from_file (data, &error);
      else
        overlay->handle =
            rsvg_handle_new_from_data ((guint8 *) data, size, &error);
      if (error || overlay->handle == NULL) {
        if (error) {
          GST_ERROR_OBJECT (overlay, "Cannot read SVG data: %s\n%s",
              error->message, data);
          g_error_free (error);
        } else {
          GST_ERROR_OBJECT (overlay, "Cannot read SVG data: %s", data);
        }
      } else {

        RsvgDimensionData svg_dimension;
        rsvg_handle_get_dimensions (overlay->handle, &svg_dimension);
        overlay->svg_width = svg_dimension.width;
        overlay->svg_height = svg_dimension.height;
        gst_base_transform_set_passthrough (btrans, FALSE);
        GST_INFO_OBJECT (overlay, "updated SVG, %d x %d", overlay->svg_width,
            overlay->svg_height);
      }
    }
  }
}
