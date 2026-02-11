_ibus_get_active_engines (BusIBusImpl     *ibus,
                          GDBusConnection *connection,
                          GError         **error)
{
    GVariantBuilder builder;
    GList *p;

    if (error) {
        *error = NULL;
    }

    g_variant_builder_init (&builder, G_VARIANT_TYPE ("av"));

    for (p = ibus->register_engine_list; p != NULL; p = p->next) {
        g_variant_builder_add (
                &builder, "v",
                ibus_serializable_serialize ((IBusSerializable *) p->data));
    }

    return g_variant_builder_end (&builder);
}
