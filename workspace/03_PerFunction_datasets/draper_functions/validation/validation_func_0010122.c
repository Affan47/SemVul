gwy_container_gis_value_of_type(GwyContainer *container,
                                GQuark key,
                                GType type)
{
    GValue *p;

    if (!key)
        return NULL;
    g_return_val_if_fail(GWY_IS_CONTAINER(container), NULL);

    p = (GValue*)g_hash_table_lookup(container->values, GUINT_TO_POINTER(key));
    if (!p)
        return NULL;
    if (type && !G_VALUE_HOLDS(p, type)) {
        g_warning("%s: trying to get %s as %s, key %u (%s)",
                  GWY_CONTAINER_TYPE_NAME,
                  G_VALUE_TYPE_NAME(p), g_type_name(type),
                  key, g_quark_to_string(key));
        return NULL;
    }

    return p;
}
