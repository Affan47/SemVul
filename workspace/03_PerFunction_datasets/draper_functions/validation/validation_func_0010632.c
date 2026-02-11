mono_metadata_get_generic_inst (int type_argc, MonoType **type_argv)
{
	MonoGenericInst *ginst;
	gboolean is_open;
	int i;
	int size = MONO_SIZEOF_GENERIC_INST + type_argc * sizeof (MonoType *);
	CollectData data;
	MonoImageSet *set;

	for (i = 0; i < type_argc; ++i)
		if (mono_class_is_open_constructed_type (type_argv [i]))
			break;
	is_open = (i < type_argc);

	ginst = g_alloca (size);
	memset (ginst, 0, sizeof (MonoGenericInst));
	ginst->is_open = is_open;
	ginst->type_argc = type_argc;
	memcpy (ginst->type_argv, type_argv, type_argc * sizeof (MonoType *));

	mono_loader_lock ();

	collect_data_init (&data);

	collect_ginst_images (ginst, &data);

	set = get_image_set (data.images, data.nimages);

	collect_data_free (&data);

	ginst = g_hash_table_lookup (set->ginst_cache, ginst);
	if (!ginst) {
		ginst = mono_image_set_alloc0 (set, size);
#ifndef MONO_SMALL_CONFIG
		ginst->id = ++next_generic_inst_id;
#endif
		ginst->is_open = is_open;
		ginst->type_argc = type_argc;

		for (i = 0; i < type_argc; ++i)
			ginst->type_argv [i] = mono_metadata_type_dup (NULL, type_argv [i]);

		g_hash_table_insert (set->ginst_cache, ginst, ginst);
	}

	mono_loader_unlock ();
	return ginst;
}
