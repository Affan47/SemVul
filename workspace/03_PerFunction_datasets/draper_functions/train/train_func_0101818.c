enterprise_permit_user_login (UmAccountDialog *self)
{
        UmRealmCommon *common;
        gchar *login;
        const gchar *add[2];
        const gchar *remove[1];
        GVariant *options;

        common = um_realm_object_get_common (self->selected_realm);

        login = um_realm_calculate_login (common, gtk_entry_get_text (self->enterprise_login));
        g_return_if_fail (login != NULL);

        add[0] = login;
        add[1] = NULL;
        remove[0] = NULL;

        g_debug ("Permitting login for: %s", login);
        options = g_variant_new_array (G_VARIANT_TYPE ("{sv}"), NULL, 0);

        um_realm_common_call_change_login_policy (common, "",
                                                  add, remove, options,
                                                  self->cancellable,
                                                  on_permit_user_login,
                                                  g_object_ref (self));

        g_object_unref (common);
        g_free (login);
}
