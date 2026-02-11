rsvg_handle_get_pixbuf_sub (RsvgHandle * handle, const char *id)
{
    RsvgDimensionData dimensions;
    GdkPixbuf *output = NULL;
    cairo_surface_t *surface;
    cairo_t *cr;

    g_return_val_if_fail (handle != NULL, NULL);

    if (!handle->priv->finished)
        return NULL;

    rsvg_handle_get_dimensions (handle, &dimensions);
    if (!(dimensions.width && dimensions.height))
        return NULL;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                          dimensions.width, dimensions.height);
    if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy (surface);
        return NULL;
    }

    cr = cairo_create (surface);

    if (!rsvg_handle_render_cairo_sub (handle, cr, id)) {
        cairo_destroy (cr);
        cairo_surface_destroy (surface);
        return NULL;
    }

    cairo_destroy (cr);

    output = rsvg_cairo_surface_to_pixbuf (surface);
    cairo_surface_destroy (surface);

    return output;
}
