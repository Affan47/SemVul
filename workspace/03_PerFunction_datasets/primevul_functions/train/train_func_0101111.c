mono_image_get_generic_param_info (MonoReflectionGenericParam *gparam, guint32 owner, MonoDynamicImage *assembly)
{
	GenericParamTableEntry *entry;


	entry = g_new0 (GenericParamTableEntry, 1);
	entry->owner = owner;

	MOVING_GC_REGISTER (&entry->gparam);
	entry->gparam = gparam;

	g_ptr_array_add (assembly->gen_params, entry);
}
