gwy_tool_grain_remover_selection_finished(GwyPlainTool *plain_tool)
{
    gdouble point[2];
    GQuark quarks[2];
    gint col, row;
    RemoveMode mode;
    GwyDataField *tmp;

    if (!plain_tool->mask_field
        || !gwy_selection_get_object(plain_tool->selection, 0, point))
        return;

    row = floor(gwy_data_field_rtoi(plain_tool->mask_field, point[1]));
    col = floor(gwy_data_field_rtoj(plain_tool->mask_field, point[0]));
    if (!gwy_data_field_get_val(plain_tool->mask_field, col, row))
        return;

    mode = GWY_TOOL_GRAIN_REMOVER(plain_tool)->args.mode;
    quarks[0] = quarks[1] = 0;
    if (mode & GRAIN_REMOVE_DATA)
        quarks[0] = gwy_app_get_data_key_for_id(plain_tool->id);
    if (mode & GRAIN_REMOVE_MASK)
        quarks[1] = gwy_app_get_mask_key_for_id(plain_tool->id);

    gwy_app_undo_qcheckpointv(plain_tool->container, 2, quarks);
    if (mode & GRAIN_REMOVE_DATA) {
        tmp = gwy_data_field_duplicate(plain_tool->mask_field);
        gwy_data_field_grains_extract_grain(tmp, col, row);
        switch (GWY_TOOL_GRAIN_REMOVER(plain_tool)->args.method) {
            case GRAIN_REMOVE_LAPLACE:
            laplace_interpolation(plain_tool->data_field, tmp);
            break;

            case GRAIN_REMOVE_FRACTAL:
            gwy_data_field_fractal_correction(plain_tool->data_field, tmp,
                                              GWY_INTERPOLATION_LINEAR);
            break;
        }
        g_object_unref(tmp);
        gwy_data_field_data_changed(plain_tool->data_field);
    }
    if (mode & GRAIN_REMOVE_MASK) {
        gwy_data_field_grains_remove_grain(plain_tool->mask_field, col, row);
        gwy_data_field_data_changed(plain_tool->mask_field);
    }

    gwy_selection_clear(plain_tool->selection);
}
