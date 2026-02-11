load_gfxfile(const char *filename)
{
  struct sprite *new = fc_malloc(sizeof(*new));

  new->surface = cairo_image_surface_create_from_png(filename);

  if (cairo_surface_status(new->surface) != CAIRO_STATUS_SUCCESS) {
    log_fatal("Failed reading graphics file: \"%s\"", filename);
    exit(EXIT_FAILURE);
  }

  return new;
}
