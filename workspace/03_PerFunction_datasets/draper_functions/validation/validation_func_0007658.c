extract_scanned_data(MDTScannedDataFrame *dataframe)
{
    GwyDataField *dfield;
    GwySIUnit *siunitxy, *siunitz;
    guint i;
    gdouble *data;
    gdouble xreal, yreal, zscale;
    gint power10xy, power10z;
    const gint16 *p;
    const gchar *unit;

    if (dataframe->x_scale.unit != dataframe->y_scale.unit)
        g_warning("Different x and y units, using x for both (incorrect).");
    unit = gwy_flat_enum_to_string(dataframe->x_scale.unit,
                                   G_N_ELEMENTS(mdt_units),
                                   mdt_units, mdt_units_name);
    siunitxy = gwy_si_unit_new_parse(unit, &power10xy);
    xreal = dataframe->fm_xres*pow10(power10xy)*dataframe->x_scale.step;
    yreal = dataframe->fm_yres*pow10(power10xy)*dataframe->y_scale.step;

    unit = gwy_flat_enum_to_string(dataframe->z_scale.unit,
                                   G_N_ELEMENTS(mdt_units),
                                   mdt_units, mdt_units_name);
    siunitz = gwy_si_unit_new_parse(unit, &power10z);
    zscale = pow10(power10z)*dataframe->z_scale.step;

    dfield = gwy_data_field_new(dataframe->fm_xres, dataframe->fm_yres,
                                xreal, yreal,
                                FALSE);
    gwy_data_field_set_si_unit_xy(dfield, siunitxy);
    g_object_unref(siunitxy);
    gwy_data_field_set_si_unit_z(dfield, siunitz);
    g_object_unref(siunitz);

    data = gwy_data_field_get_data(dfield);
    p = (gint16*)dataframe->image;
    for (i = 0; i < dataframe->fm_xres*dataframe->fm_yres; i++)
        data[i] = pow10(power10z)*dataframe->z_scale.offset
                  + zscale*GINT16_FROM_LE(p[i]);

    gwy_data_field_invert(dfield, TRUE, FALSE, FALSE);

    return dfield;
}
