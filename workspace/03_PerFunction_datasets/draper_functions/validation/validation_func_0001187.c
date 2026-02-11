ibus_config_service_set_value (IBusConfigService *config,
                               const gchar       *section,
                               const gchar       *name,
                               GVariant          *value,
                               GError           **error)
{
    if (error) {
        gchar *str = g_variant_print (value, TRUE);
        *error = g_error_new (G_DBUS_ERROR, G_DBUS_ERROR_FAILED,
                              "Cannot set value %s::%s to %s", section, name, str);
        g_free (str);
    }
    return FALSE;
}
