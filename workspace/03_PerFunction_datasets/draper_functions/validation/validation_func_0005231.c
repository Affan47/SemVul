gnc_gdate_set_prev_fiscal_year_start (GDate *date,
                                      const GDate *fy_end)
{
    g_return_if_fail(date);
    g_return_if_fail(fy_end);

    gnc_gdate_set_fiscal_year_start(date, fy_end);
    g_date_subtract_years(date, 1);
}
