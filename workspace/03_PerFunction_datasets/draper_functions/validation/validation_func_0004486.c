gwy_data_field_grains_get_values(GwyDataField *data_field,
                                 gdouble *values,
                                 gint ngrains,
                                 const gint *grains,
                                 GwyGrainQuantity quantity)
{
    gdouble *allvalues[1];

    if (!values)
        values = g_new(gdouble, ngrains + 1);

    allvalues[0] = values;
    gwy_data_field_grains_get_quantities(data_field, allvalues,
                                         &quantity, 1, ngrains, grains);
    return values;
}
