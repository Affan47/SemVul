rsvg_filter_render (RsvgFilter *self,
                    cairo_surface_t *source,
                    RsvgDrawingCtx *context,
                    RsvgBbox *bounds,
                    char *channelmap)
{
    RsvgFilterContext *ctx;
    RsvgFilterPrimitive *current;
    guint i;
    cairo_surface_t *output;

    g_return_val_if_fail (source != NULL, NULL);
    g_return_val_if_fail (cairo_surface_get_type (source) == CAIRO_SURFACE_TYPE_IMAGE, NULL);

    ctx = g_new (RsvgFilterContext, 1);
    ctx->filter = self;
    ctx->source_surface = source;
    ctx->bg_surface = NULL;
    ctx->results = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, rsvg_filter_free_pair);
    ctx->ctx = context;

    rsvg_filter_fix_coordinate_system (ctx, rsvg_current_state (context), bounds);

    ctx->lastresult.surface = cairo_surface_reference (source);
    ctx->lastresult.Rused = 1;
    ctx->lastresult.Gused = 1;
    ctx->lastresult.Bused = 1;
    ctx->lastresult.Aused = 1;
    ctx->lastresult.bounds = rsvg_filter_primitive_get_bounds (NULL, ctx);

    for (i = 0; i < 4; i++)
        ctx->channelmap[i] = channelmap[i] - '0';

    for (i = 0; i < self->super.children->len; i++) {
        current = g_ptr_array_index (self->super.children, i);
        if (RSVG_NODE_IS_FILTER_PRIMITIVE (&current->super))
            rsvg_filter_primitive_render (current, ctx);
    }

    output = ctx->lastresult.surface;

    g_hash_table_destroy (ctx->results);

    rsvg_filter_context_free (ctx);

    return output;
}
