gt_graphics_cairo_save_to_stream(const GtGraphics *gg, GtStr *stream)
{
  const GtGraphicsCairo *g = (const GtGraphicsCairo*) gg;
  GT_UNUSED cairo_status_t rval;
  cairo_surface_t *bgsurf = NULL;
  cairo_t *bgc = NULL;
  gt_assert(g && stream);


  if (g->from_context)
    return;
  switch (g->type)
  {
    case GT_GRAPHICS_PNG:

      bgsurf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, g->width,
                                          g->height);
      bgc = cairo_create(bgsurf);
      cairo_set_source_rgba(bgc, g->bg_color.red, g->bg_color.green,
                                 g->bg_color.blue, g->bg_color.alpha);
      cairo_paint(bgc);
      cairo_set_source_surface(bgc, g->surf, 0, 0);
      cairo_paint(bgc);
      rval = cairo_surface_write_to_png_stream(bgsurf, str_write_func, stream);
      gt_assert(rval == CAIRO_STATUS_SUCCESS);
      cairo_destroy(bgc);
      cairo_surface_destroy(bgsurf);
      break;
    default:
      cairo_show_page(g->cr);
      cairo_surface_flush(g->surf);
      cairo_surface_finish(g->surf);
      gt_str_reset(stream);
      gt_str_append_str(stream, g->outbuf);
      gt_assert(gt_str_length(stream) > 0);
  }
}
