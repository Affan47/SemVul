setSoftMaskFromImageMask(GfxState *state, Object *ref, Stream *str,
                                                   int width, int height, GBool invert,
                                                   GBool inlineImg, double *baseMatrix)
{
  cairo_t *cr;
  cairo_surface_t *surface;
  double x1, y1, x2, y2;
  CairoImage *image;

  getBBox(state, width, height, &x1, &y1, &x2, &y2);

  image = new CairoImage (x1, y1, x2, y2);
  saveImage (image);

  if (imgDrawCbk && imgDrawCbk (numImages - 1, imgDrawCbkData)) {
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (surface);
    setCairo (cr);
    cairo_translate (cr, 0, height);
    cairo_scale (cr, width, -height);

    CairoOutputDev::drawImageMask(state, ref, str, width, height, invert, inlineImg, gFalse);
    if (state->getFillColorSpace()->getMode() == csPattern) {
      cairo_mask (cairo, mask);
    }
    image->setImage (surface);

    setCairo (NULL);
    cairo_surface_destroy (surface);
    cairo_destroy (cr);
  }
}
