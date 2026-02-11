gwy_data_view_destroy(GtkObject *object)
{
    GwyDataView *data_view;

    g_return_if_fail(GWY_IS_DATA_VIEW(object));

    data_view = GWY_DATA_VIEW(object);
    gwy_data_view_disconnect_data(data_view);
    gwy_data_view_set_layer(data_view, &data_view->top_layer, NULL, NULL,
                            GWY_DATA_VIEW_LAYER_TOP);
    gwy_data_view_set_layer(data_view, &data_view->alpha_layer,
                            &data_view->alpha_hid, NULL,
                            GWY_DATA_VIEW_LAYER_ALPHA);
    gwy_data_view_set_layer(data_view, &data_view->base_layer,
                            &data_view->base_hid, NULL,
                            GWY_DATA_VIEW_LAYER_BASE);

    GTK_OBJECT_CLASS(gwy_data_view_parent_class)->destroy(object);
}
