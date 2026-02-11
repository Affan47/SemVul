mx_texture_cache_get_actor (MxTextureCache *self,
                            const gchar    *uri)
{
  ClutterTexture *tex;

  g_return_val_if_fail (MX_IS_TEXTURE_CACHE (self), NULL);
  g_return_val_if_fail (uri != NULL, NULL);

  if ((tex = mx_texture_cache_get_texture (self, uri)))
    return CLUTTER_ACTOR (tex);
  else
    return NULL;
}
