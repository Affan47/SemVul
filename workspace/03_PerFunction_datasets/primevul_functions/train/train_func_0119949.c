ephy_embed_single_class_init (EphyEmbedSingleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = ephy_embed_single_finalize;
  object_class->get_property = ephy_embed_single_get_property;
  object_class->set_property = ephy_embed_single_set_property;


  g_signal_new ("new-window",
                EPHY_TYPE_EMBED_SINGLE,
                G_SIGNAL_RUN_FIRST | G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (EphyEmbedSingleClass, new_window),
                ephy_signal_accumulator_object, ephy_embed_get_type,
                ephy_marshal_OBJECT__OBJECT_FLAGS,
                GTK_TYPE_WIDGET,
                2,
                GTK_TYPE_WIDGET,
                EPHY_TYPE_WEB_VIEW_CHROME);


  g_signal_new ("handle_content",
                EPHY_TYPE_EMBED_SINGLE,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (EphyEmbedSingleClass, handle_content),
                g_signal_accumulator_true_handled, NULL,
                ephy_marshal_BOOLEAN__STRING_STRING,
                G_TYPE_BOOLEAN,
                2,
                G_TYPE_STRING,
                G_TYPE_STRING);


  g_signal_new ("add-sidebar",
                EPHY_TYPE_EMBED_SINGLE,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (EphyEmbedSingleClass, add_sidebar),
                g_signal_accumulator_true_handled, NULL,
                ephy_marshal_BOOLEAN__STRING_STRING,
                G_TYPE_BOOLEAN,
                2,
                G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE,
                G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE);


  g_signal_new ("add-search-engine",
                EPHY_TYPE_EMBED_SINGLE,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (EphyEmbedSingleClass, add_search_engine),
                g_signal_accumulator_true_handled, NULL,
                ephy_marshal_BOOLEAN__STRING_STRING_STRING,
                G_TYPE_BOOLEAN,
                3,
                G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE,
                G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE,
                G_TYPE_STRING | G_SIGNAL_TYPE_STATIC_SCOPE);


  g_object_class_install_property
    (object_class,
     PROP_NETWORK_STATUS,
     g_param_spec_boolean ("network-status",
                           "network-status",
                           "network-status",
                           FALSE,
                           G_PARAM_READWRITE | G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB));

  g_type_class_add_private (object_class, sizeof (EphyEmbedSinglePrivate));
}
