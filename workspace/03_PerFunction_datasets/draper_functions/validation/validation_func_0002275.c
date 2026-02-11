_st_create_shadow_cairo_pattern (StShadow        *shadow_spec,
                                 cairo_pattern_t *src_pattern)
{
  static cairo_user_data_key_t shadow_pattern_user_data;
  cairo_t *cr;
  cairo_surface_t *src_surface;
  cairo_surface_t *surface_in;
  cairo_surface_t *surface_out;
  cairo_pattern_t *dst_pattern;
  guchar          *pixels_in, *pixels_out;
  gint             width_in, height_in, rowstride_in;
  gint             width_out, height_out, rowstride_out;
  cairo_matrix_t   shadow_matrix;
  int i, j;

  g_return_val_if_fail (shadow_spec != NULL, NULL);
  g_return_val_if_fail (src_pattern != NULL, NULL);

  cairo_pattern_get_surface (src_pattern, &src_surface);

  width_in  = cairo_image_surface_get_width  (src_surface);
  height_in = cairo_image_surface_get_height (src_surface);


  if (cairo_image_surface_get_format (src_surface) != CAIRO_FORMAT_A8)
    {
      surface_in = cairo_image_surface_create (CAIRO_FORMAT_A8,
                                               width_in, height_in);

      cr = cairo_create (surface_in);
      cairo_set_source_surface (cr, src_surface, 0, 0);
      cairo_paint (cr);
      cairo_destroy (cr);
    }
  else
    {
      surface_in = cairo_surface_reference (src_surface);
    }

  pixels_in = cairo_image_surface_get_data (surface_in);
  rowstride_in = cairo_image_surface_get_stride (surface_in);

  pixels_out = blur_pixels (pixels_in, width_in, height_in, rowstride_in,
                            shadow_spec->blur,
                            &width_out, &height_out, &rowstride_out);
  cairo_surface_destroy (surface_in);


  if (shadow_spec->inset)
    {
      for (j = 0; j < height_out; j++)
        {
          guchar *p = pixels_out + rowstride_out * j;
          for (i = 0; i < width_out; i++, p++)
            *p = ~*p;
        }
    }

  surface_out = cairo_image_surface_create_for_data (pixels_out,
                                                     CAIRO_FORMAT_A8,
                                                     width_out,
                                                     height_out,
                                                     rowstride_out);
  cairo_surface_set_user_data (surface_out, &shadow_pattern_user_data,
                               pixels_out, (cairo_destroy_func_t) g_free);

  dst_pattern = cairo_pattern_create_for_surface (surface_out);
  cairo_surface_destroy (surface_out);

  cairo_pattern_get_matrix (src_pattern, &shadow_matrix);

  if (shadow_spec->inset)
    {


      cairo_matrix_translate (&shadow_matrix,
                              (width_out - width_in) / 2.0,
                              (height_out - height_in) / 2.0);
      cairo_pattern_set_matrix (dst_pattern, &shadow_matrix);
      return dst_pattern;
    }


  cairo_matrix_invert (&shadow_matrix);


  cairo_matrix_translate (&shadow_matrix,
                          shadow_spec->xoffset,
                          shadow_spec->yoffset);


  cairo_matrix_translate (&shadow_matrix,
                          - shadow_spec->spread,
                          - shadow_spec->spread);


  cairo_matrix_scale (&shadow_matrix,
                      (width_in + 2.0 * shadow_spec->spread) / width_in,
                      (height_in + 2.0 * shadow_spec->spread) / height_in);


  cairo_matrix_translate (&shadow_matrix,
                          - (width_out - width_in) / 2.0,
                          - (height_out - height_in) / 2.0);


  cairo_matrix_invert (&shadow_matrix);

  cairo_pattern_set_matrix (dst_pattern, &shadow_matrix);

  return dst_pattern;
}
