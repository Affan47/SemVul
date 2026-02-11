gwy_curve_finalize (GObject *object)
{
    GwyCurve *curve;
    gint i;

    g_return_if_fail(GWY_IS_CURVE(object));

    curve = GWY_CURVE(object);
    if (curve->pixmap)
        g_object_unref(curve->pixmap);

    for (i = 0; i < curve->num_channels; i++) {
        if (curve->channel_data[i].points)
            g_free(curve->channel_data[i].points);
        if (curve->channel_data[i].ctlpoints)
            g_free(curve->channel_data[i].ctlpoints);
    }
    g_free(curve->channel_data);

    G_OBJECT_CLASS(parent_class)->finalize(object);
}
