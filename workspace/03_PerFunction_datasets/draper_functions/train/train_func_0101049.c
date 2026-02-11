set_seat_properties (Seat *seat, const gchar *config_section)
{
    gchar **keys;
    gint i;

    keys = config_get_keys (config_get_instance (), "SeatDefaults");
    for (i = 0; keys[i]; i++)
    {
        gchar *value = config_get_string (config_get_instance (), "SeatDefaults", keys[i]);
        seat_set_property (seat, keys[i], value);
        g_free (value);
    }
    g_strfreev (keys);

    if (config_section)
    {
        keys = config_get_keys (config_get_instance (), config_section);
        for (i = 0; keys[i]; i++)
        {
            gchar *value = config_get_string (config_get_instance (), config_section, keys[i]);
            seat_set_property (seat, keys[i], value);
            g_free (value);
        }
        g_strfreev (keys);
    }
}
