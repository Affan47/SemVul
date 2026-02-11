gnc_date_delta_show_polarity (GNCDateDelta *gdd, gboolean show_polarity)
{
    g_return_if_fail(gdd != NULL);
    g_return_if_fail(GNC_IS_DATE_DELTA(gdd));

    gdd->show_polarity = show_polarity;

    if (show_polarity)
        gtk_widget_show(gdd->polarity_combo);
    else
        gtk_widget_hide(gdd->polarity_combo);
}
