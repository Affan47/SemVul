gwy_sensitivity_group_contains_widget(GwySensitivityGroup *sensgroup,
                                      GtkWidget *widget)
{
    GObject *object;
    SensList *senslist;

    g_return_val_if_fail(GWY_IS_SENSITIVITY_GROUP(sensgroup), FALSE);
    g_return_val_if_fail(GTK_IS_WIDGET(widget), FALSE);
    object = G_OBJECT(widget);
    senslist = (SensList*)g_object_get_qdata(object, sensitivity_group_quark);
    if (!senslist)
        return FALSE;
    if (senslist->parent != sensgroup)
        return FALSE;

    return TRUE;
}
