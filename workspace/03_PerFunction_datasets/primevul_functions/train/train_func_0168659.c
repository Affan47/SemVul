_rsvg_node_line_draw (RsvgNode * overself, RsvgDrawingCtx * ctx, int dominate)
{
    GString *d;
    cairo_path_t *path;
    char buf[G_ASCII_DTOSTR_BUF_SIZE];
    RsvgNodeLine *self = (RsvgNodeLine *) overself;


    d = g_string_new ("M ");

    g_string_append (d, g_ascii_dtostr (buf, sizeof (buf),
                                        _rsvg_css_normalize_length (&self->x1, ctx, 'h')));
    g_string_append_c (d, ' ');
    g_string_append (d, g_ascii_dtostr (buf, sizeof (buf),
                                        _rsvg_css_normalize_length (&self->y1, ctx, 'v')));
    g_string_append (d, " L ");
    g_string_append (d, g_ascii_dtostr (buf, sizeof (buf),
                                        _rsvg_css_normalize_length (&self->x2, ctx, 'h')));
    g_string_append_c (d, ' ');
    g_string_append (d, g_ascii_dtostr (buf, sizeof (buf),
                                        _rsvg_css_normalize_length (&self->y2, ctx, 'v')));

    rsvg_state_reinherit_top (ctx, overself->state, dominate);

    path = rsvg_parse_path (d->str);
    rsvg_render_path (ctx, path);
    rsvg_cairo_path_destroy (path);

    g_string_free (d, TRUE);
}
