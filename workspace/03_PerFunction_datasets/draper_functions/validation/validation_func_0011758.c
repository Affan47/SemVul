CommandExportPositionPDF(char *sz)
{
#if HAVE_PANGOCAIRO
    gchar *filename;
    int move_nr;
    int game_nr;
    moverecord *pmr;
    cairo_surface_t *surface;
    cairo_t *cairo;

    if (!CheckGameExists())
        return;

    filename = export_get_filename(sz);
    if (!filename)
        return;
    pmr = export_get_moverecord(&game_nr, &move_nr);
    if (!pmr) {
        outputerrf(_("Cannot create export for this move"));
        return;
    }
    surface = cairo_pdf_surface_create(filename, SIMPLE_BOARD_WIDTH, SIMPLE_BOARD_HEIGHT);
    if (surface) {
        cairo = cairo_create(surface);
        draw_simple_board_on_cairo(&ms, pmr, move_nr, game_nr, cairo, SIZE_1PERPAGE);
        cairo_surface_destroy(surface);
        cairo_destroy(cairo);
    } else
#endif
        outputerrf(_("Failed to create cairo surface for %s"), sz);
}
