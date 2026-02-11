gwy_data_line_part_clear(GwyDataLine *data_line,
                         gint from, gint to)
{
    g_return_if_fail(GWY_IS_DATA_LINE(data_line));
    if (to < from)
        GWY_SWAP(gint, from, to);

    g_return_if_fail(from >= 0 && to <= data_line->res);

    memset(data_line->data + from, 0, (to - from)*sizeof(gdouble));
}
