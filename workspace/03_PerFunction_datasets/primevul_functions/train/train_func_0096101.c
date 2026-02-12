gimp_channel_get_active_components (GimpDrawable *drawable,
                                    gboolean     *active)
{

  active[GRAY]    = TRUE;
  active[ALPHA_G] = FALSE;
}
