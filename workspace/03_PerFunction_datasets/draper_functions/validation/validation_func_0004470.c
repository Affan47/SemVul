generate_session_cookie (CkManager *manager)
{
        guint32  num;
        char    *cookie;
        GTimeVal tv;
        char    *uuid;

        uuid = dbus_get_local_machine_id ();
        if (uuid == NULL) {
                uuid = g_strdup (g_get_host_name ());
        }


        cookie = NULL;
 again:
        num = (guint32)g_random_int_range (1, G_MAXINT32);

        g_get_current_time (&tv);

        g_free (cookie);
        cookie = g_strdup_printf ("%s-%ld.%ld-%u", uuid, tv.tv_sec, tv.tv_usec, num);

        if (g_hash_table_lookup (manager->priv->leaders, cookie)) {
                goto again;
        }

        g_free (uuid);

        return cookie;
}
