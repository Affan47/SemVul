meta_frames_draw (GtkWidget *widget,
                  cairo_t   *cr)
{
  MetaUIFrame *frame;
  MetaFrames *frames;
  cairo_rectangle_int_t clip;
  cairo_region_t *region;
  cairo_surface_t *target;

  frames = META_FRAMES (widget);
  target = cairo_get_target (cr);
  gdk_cairo_get_clip_rectangle (cr, &clip);

  g_assert (cairo_surface_get_type (target) == CAIRO_SURFACE_TYPE_XLIB);
  frame = meta_frames_lookup_window (frames, cairo_xlib_surface_get_drawable (target));
  if (frame == NULL)
    return FALSE;

  region = cairo_region_create_rectangle (&clip);
  clip_region_to_visible_frame_border (region, frame);

  if (cairo_region_is_empty (region))
    goto out;

  gdk_cairo_region (cr, region);
  cairo_clip (cr);

  cairo_save (cr);
  setup_bg_cr (cr, frame->window, 0, 0);
  cairo_paint (cr);
  cairo_restore (cr);

  meta_frames_paint (frames, frame, cr);

 out:
  cairo_region_destroy (region);

  return TRUE;
}
