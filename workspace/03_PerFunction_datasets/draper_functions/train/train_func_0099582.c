gnucash_sheet_get_header_widths (GnucashSheet *sheet,
                                 GNCHeaderWidths widths)
{
    SheetBlockStyle *style;
    CellBlock *header;
    int row, col;

    g_return_if_fail (sheet != NULL);
    g_return_if_fail (GNUCASH_IS_SHEET(sheet));

    style = gnucash_sheet_get_style_from_cursor (sheet, CURSOR_HEADER);
    g_return_if_fail (style != NULL);

    header = style->cursor;
    g_return_if_fail (header != NULL);

    for (row = 0; row < style->nrows; row++)
        for (col = 0; col < style->ncols; col++)
        {
            CellDimensions *cd;
            BasicCell *cell;

            cd = gnucash_style_get_cell_dimensions (style,
                                                    row, col);
            if (cd == NULL)
                continue;

            cell = gnc_cellblock_get_cell (header, row, col);
            if (!cell || !cell->cell_name)
                continue;

            gnc_header_widths_set_width (widths,
                                         cell->cell_name,
                                         cd->pixel_width);
        }
}
