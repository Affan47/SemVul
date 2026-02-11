gwy_data_field_grains_get_distribution(GwyDataField *data_field,
                                       GwyDataField *grain_field,
                                       GwyDataLine *distribution,
                                       gint ngrains,
                                       const gint *grains,
                                       GwyGrainQuantity quantity,
                                       gint nstats)
{
    GwyDataLine *values;
    gint *mygrains = NULL;

    g_return_val_if_fail(GWY_IS_DATA_FIELD(data_field), FALSE);
    g_return_val_if_fail(grains || GWY_IS_DATA_FIELD(grain_field), FALSE);
    g_return_val_if_fail(!grain_field
                         || (grain_field->xres == data_field->xres
                             && grain_field->yres == data_field->yres), FALSE);
    g_return_val_if_fail(!distribution || GWY_IS_DATA_LINE(distribution),
                         FALSE);


    if (!grains) {
        grains = mygrains = g_new0(gint, grain_field->xres*grain_field->yres);
        ngrains = gwy_data_field_number_grains(grain_field, mygrains);
    }
    if (!ngrains) {
        g_free(mygrains);
        return NULL;
    }

    values = gwy_data_line_new(ngrains + 1, 1.0, FALSE);
    gwy_data_field_grains_get_values(data_field, values->data,
                                     ngrains, grains, quantity);
    g_free(mygrains);

    if (!distribution)
        distribution = gwy_data_line_new(1, 1.0, FALSE);

    gwy_data_line_distribution(values, distribution, 0.0, 0.0, FALSE, nstats);

    return distribution;
}
