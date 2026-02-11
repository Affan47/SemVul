print_implemented_interfaces (MonoClass *klass) {
	char *name;
	MonoError error;
	GPtrArray *ifaces = NULL;
	int i;
	int ancestor_level = 0;

	name = mono_type_get_full_name (klass);
	printf ("Packed interface table for class %s has size %d\n", name, klass->interface_offsets_count);
	g_free (name);

	for (i = 0; i < klass->interface_offsets_count; i++)
		printf ("  [%03d][UUID %03d][SLOT %03d][SIZE  %03d] interface %s.%s\n", i,
				klass->interfaces_packed [i]->interface_id,
				klass->interface_offsets_packed [i],
				klass->interfaces_packed [i]->method.count,
				klass->interfaces_packed [i]->name_space,
				klass->interfaces_packed [i]->name );
	printf ("Interface flags: ");
	for (i = 0; i <= klass->max_interface_id; i++)
		if (MONO_CLASS_IMPLEMENTS_INTERFACE (klass, i))
			printf ("(%d,T)", i);
		else
			printf ("(%d,F)", i);
	printf ("\n");
	printf ("Dump interface flags:");
#ifdef COMPRESSED_INTERFACE_BITMAP
	{
		const uint8_t* p = klass->interface_bitmap;
		i = klass->max_interface_id;
		while (i > 0) {
			printf (" %d x 00 %02X", p [0], p [1]);
			i -= p [0] * 8;
			i -= 8;
		}
	}
#else
	for (i = 0; i < ((((klass->max_interface_id + 1) >> 3)) + (((klass->max_interface_id + 1) & 7)? 1 :0)); i++)
		printf (" %02X", klass->interface_bitmap [i]);
#endif
	printf ("\n");
	while (klass != NULL) {
		printf ("[LEVEL %d] Implemented interfaces by class %s:\n", ancestor_level, klass->name);
		ifaces = mono_class_get_implemented_interfaces (klass, &error);
		if (!mono_error_ok (&error)) {
			printf ("  Type failed due to %s\n", mono_error_get_message (&error));
			mono_error_cleanup (&error);
		} else if (ifaces) {
			for (i = 0; i < ifaces->len; i++) {
				MonoClass *ic = g_ptr_array_index (ifaces, i);
				printf ("  [UIID %d] interface %s\n", ic->interface_id, ic->name);
				printf ("  [%03d][UUID %03d][SLOT %03d][SIZE  %03d] interface %s.%s\n", i,
						ic->interface_id,
						mono_class_interface_offset (klass, ic),
						ic->method.count,
						ic->name_space,
						ic->name );
			}
			g_ptr_array_free (ifaces, TRUE);
		}
		ancestor_level ++;
		klass = klass->parent;
	}
}
