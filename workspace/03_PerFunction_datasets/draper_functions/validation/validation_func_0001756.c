webx_preview_zoom_combo_changed (GtkWidget     *combo,
                                 WebxPreview   *preview)
{
  gint          index;

  g_return_if_fail (WEBX_IS_PREVIEW (preview));

  if (! gimp_int_combo_box_get_active (GIMP_INT_COMBO_BOX (combo), &index))
    return;

  if (index >= 0 && index < G_N_ELEMENTS (webx_zoomlevels))
    {
      webx_preview_zoom (preview, webx_zoomlevels[index]);
    }
  else
    {
      if (index == G_N_ELEMENTS (webx_zoomlevels))
        {
          webx_preview_set_zoom_mode (preview,
                                      WEBX_ZOOM_MODE_FIT_WIDTH);
        }
      else
        {
          webx_preview_set_zoom_mode (preview,
                                      WEBX_ZOOM_MODE_FIT_VISIBLE);
        }
    }
}
