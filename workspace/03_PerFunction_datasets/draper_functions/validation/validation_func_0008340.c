handleMarkerInStream (PJDEC_INST g)
{
    BYTE marker;

    marker = mar_get(g);

    if (marker == MARKER_EOI) {
        PRINT (_T("handleMarkerInStream: parsed EOI\n"), 0, 0);
        g->got_EOI = TRUE;
    } else if (marker == MARKER_DNL) {
        PRINT (_T("handleMarkerInStream: parsing DNL\n"), 0, 0);
        mar_parse_dnl (g);
    } else if (g->restart_interval > 0
        && g->restart_cur_mcu == g->restart_interval
        && (marker-MARKER_RST0) == g->restart_cur_marker)
    {

        PRINT (_T("handleMarkerInStream: parsed expected RST\n"), 0, 0);
        g->restart_cur_marker = (g->restart_cur_marker+1) & 7;
        g->restart_cur_mcu = 0;
        zero_prior_DC (g);
    } else {
        PRINT (_T("handleMarkerInStream: illegal marker=0x%2.2X\n"), marker, 0);
        longjmp (g->syntax_error, BAD_MARKER_DATA);
    }
}
