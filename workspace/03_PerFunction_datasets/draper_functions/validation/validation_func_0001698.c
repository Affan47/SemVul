graph_selected(GwySelection* selection,
               gint i,
               FitControls *controls)
{
    FitArgs *args;
    gchar buffer[24];
    gdouble range[2];
    gint nselections;
    gdouble power10;

    g_return_if_fail(i <= 0);

    args = controls->args;
    nselections = gwy_selection_get_data(selection, NULL);
    gwy_selection_get_object(selection, 0, range);

    if (nselections <= 0 || range[0] == range[1])
        fit_get_full_x_range(controls, &args->from, &args->to);
    else {
        args->from = MIN(range[0], range[1]);
        args->to = MAX(range[0], range[1]);
    }
    controls->in_update = TRUE;
    power10 = pow10(args->abscissa_vf->precision);
    g_snprintf(buffer, sizeof(buffer), "%.*f",
               args->abscissa_vf->precision,
               floor(args->from*power10/args->abscissa_vf->magnitude)/power10);
    gtk_entry_set_text(GTK_ENTRY(controls->from), buffer);
    g_snprintf(buffer, sizeof(buffer), "%.*f",
               args->abscissa_vf->precision,
               ceil(args->to*power10/args->abscissa_vf->magnitude)/power10);
    gtk_entry_set_text(GTK_ENTRY(controls->to), buffer);
    controls->in_update = FALSE;

    fit_set_state(controls, FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(controls->draw_circle),
                                 FALSE);
}
