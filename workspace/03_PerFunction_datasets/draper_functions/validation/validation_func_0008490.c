setting_is_visible(const struct setting *pset,
                        struct connection *caller)
{
  return (!caller
          || pset->to_client
          || caller->access_level >= ALLOW_HACK);
}
