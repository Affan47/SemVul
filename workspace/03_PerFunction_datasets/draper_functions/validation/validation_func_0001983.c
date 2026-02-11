contact_set_avatar_token (TpContact *self, const gchar *new_token,
    gboolean request)
{


  if ((self->priv->has_features & CONTACT_FEATURE_FLAG_AVATAR_TOKEN) &&
      !tp_strdiff (self->priv->avatar_token, new_token))
    return;

  DEBUG ("contact#%u token is %s", self->priv->handle, new_token);

  self->priv->has_features |= CONTACT_FEATURE_FLAG_AVATAR_TOKEN;
  g_free (self->priv->avatar_token);
  self->priv->avatar_token = g_strdup (new_token);
  g_object_notify ((GObject *) self, "avatar-token");

  if (request && tp_contact_has_feature (self, TP_CONTACT_FEATURE_AVATAR_DATA))
    contact_update_avatar_data (self);
}
