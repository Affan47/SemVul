_init_standard_transition_assets (void)
{
  guint i;

  for (i = 1; i < G_N_ELEMENTS (transition_types) - 1; i++) {
    GESAsset *asset = ges_asset_request (GES_TYPE_TRANSITION_CLIP,
        transition_types[i].value_nick, NULL);

    ges_meta_container_register_meta_string (GES_META_CONTAINER (asset),
        GES_META_READABLE, GES_META_DESCRIPTION,
        transition_types[i].value_name);
  }

}
