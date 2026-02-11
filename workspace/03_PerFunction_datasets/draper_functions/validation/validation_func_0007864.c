gnc_date_format_compute_format(GNCDateFormat *gdf)
{
    g_return_if_fail(gdf);
    g_return_if_fail(GNC_IS_DATE_FORMAT(gdf));


    gnc_date_format_refresh(gdf);


    g_signal_emit(G_OBJECT(gdf), date_format_signals[FORMAT_CHANGED], 0);
}
