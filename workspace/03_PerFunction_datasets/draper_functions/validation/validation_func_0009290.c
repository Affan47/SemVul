gupnp_service_action_get_values (GUPnPServiceAction *action,
                                 GList              *arg_names,
                                 GList              *arg_types)
{
        GList *arg_values;
        guint i;

        g_return_val_if_fail (action != NULL, NULL);

        arg_values = NULL;

        for (i = 0; i < g_list_length (arg_names); i++) {
                const char *arg_name;
                GType arg_type;
                GValue *arg_value;

                arg_name = (const char *) g_list_nth_data (arg_names, i);
                arg_type = (GType) g_list_nth_data (arg_types, i);

                arg_value = g_slice_new0 (GValue);
                g_value_init (arg_value, arg_type);

                gupnp_service_action_get_value (action, arg_name, arg_value);

                arg_values = g_list_append (arg_values, arg_value);
        }

        return arg_values;
}
