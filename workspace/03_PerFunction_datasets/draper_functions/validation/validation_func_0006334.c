p_generate_outline_shape_workpoints(GapMorphGUIParams *mgup)
{
  GapMorphWorkPoint *wp;
  GimpPixelFetcher *src_pixfet;
  GimpPixelFetcher *dst_pixfet;
  GimpDrawable *dst_drawable;
  GimpDrawable *src_drawable;
  gdouble alpha_rad;
  gdouble step_rad;
  gint  ii;

  src_drawable = gimp_drawable_get (mgup->mgpp->osrc_layer_id);
  dst_drawable = gimp_drawable_get (mgup->mgpp->fdst_layer_id);

  src_pixfet = gimp_pixel_fetcher_new (src_drawable, FALSE );
  dst_pixfet = gimp_pixel_fetcher_new (dst_drawable, FALSE );

  step_rad =  (2.0 * G_PI) / MAX(1, mgup->num_shapepoints);
  alpha_rad = 0.0;


  for(ii=0; ii < mgup->num_shapepoints; ii++)
  {
     gdouble sx, sy, dx, dy;

     p_find_outmost_opaque_pixel(src_pixfet
                                ,src_drawable->bpp
                                ,alpha_rad
                                ,src_drawable->width
                                ,src_drawable->height
                                ,&sx
                                ,&sy
                                );
     p_find_outmost_opaque_pixel(dst_pixfet
                                ,dst_drawable->bpp
                                ,alpha_rad
                                ,dst_drawable->width
                                ,dst_drawable->height
                                ,&dx
                                ,&dy
                                );


     wp = gap_morph_dlg_new_workpont(sx ,sy ,dx ,dy);
     wp->next = mgup->mgpp->master_wp_list;
     mgup->mgpp->master_wp_list = wp;

     alpha_rad += step_rad;
  }
  gimp_pixel_fetcher_destroy (src_pixfet);
  gimp_pixel_fetcher_destroy (dst_pixfet);

  gimp_drawable_detach(src_drawable);
  gimp_drawable_detach(dst_drawable);


}
