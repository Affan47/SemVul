averaging(GwyContainer *data, GwyRunType run)
{
    GwyDataField *dfield, *score;
    GwyContainer *mydata;
    gint id, newid;

    g_return_if_fail(run & AVERAGING_RUN_MODES);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     0);
    g_return_if_fail(GWY_IS_DATA_FIELD(dfield));

    mydata = gwy_container_new();
    gwy_container_set_object_by_name(mydata, "/0/data", dfield);
    gwy_app_sync_data_items(data, mydata, id, 0, FALSE,
                            GWY_DATA_ITEM_REAL_SQUARE,
                            0);

    score = averaging_dialog(mydata);
    if (score) {
        newid = gwy_app_data_browser_add_data_field(score, data, TRUE);
        gwy_app_sync_data_items(mydata, data, 0, newid, FALSE,
                            GWY_DATA_ITEM_GRADIENT,
                            GWY_DATA_ITEM_MASK_COLOR,
                            GWY_DATA_ITEM_RANGE,
                            GWY_DATA_ITEM_RANGE_TYPE,
                            GWY_DATA_ITEM_REAL_SQUARE,
                            0);
        gwy_app_set_data_field_title(data, newid, _("Averaged"));

        g_object_unref(score);
    }
    g_object_unref(mydata);
}
