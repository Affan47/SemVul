font_measure_full(const RrFont *f, const gchar *str,
                              gint *x, gint *y, gint shadow_x, gint shadow_y,
                              gboolean flow, gint maxwidth)
{
    PangoRectangle rect;

    pango_layout_set_text(f->layout, str, -1);
    if (flow) {
        pango_layout_set_single_paragraph_mode(f->layout, FALSE);
        pango_layout_set_width(f->layout, maxwidth * PANGO_SCALE);
        pango_layout_set_ellipsize(f->layout, PANGO_ELLIPSIZE_NONE);
    }
    else {

        pango_layout_set_single_paragraph_mode(f->layout, TRUE);
        pango_layout_set_width(f->layout, -1);
        pango_layout_set_ellipsize(f->layout, PANGO_ELLIPSIZE_MIDDLE);
    }


    pango_layout_get_extents(f->layout, NULL, &rect);
#if PANGO_VERSION_MAJOR > 1 || \
    (PANGO_VERSION_MAJOR == 1 && PANGO_VERSION_MINOR >= 16)


    pango_extents_to_pixels(&rect, NULL);
#else
    rect.width = (rect.width + PANGO_SCALE - 1) / PANGO_SCALE;
    rect.height = (rect.height + PANGO_SCALE - 1) / PANGO_SCALE;
#endif
    *x = rect.width + ABS(shadow_x) + 4 ;
    *y = rect.height + ABS(shadow_y);
}
