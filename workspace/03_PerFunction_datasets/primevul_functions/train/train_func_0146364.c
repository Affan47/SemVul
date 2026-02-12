type_from_name (const char *str, MonoBoolean ignoreCase)
{
	MonoType *type = NULL;
	MonoAssembly *assembly = NULL;
	MonoTypeNameParse info;
	char *temp_str = g_strdup (str);
	gboolean type_resolve = FALSE;

	MONO_ARCH_SAVE_REGS;


	if (!mono_reflection_parse_type (temp_str, &info)) {
		mono_reflection_free_type_info (&info);
		g_free (temp_str);
		return NULL;
	}

	if (info.assembly.name) {
		assembly = mono_assembly_load (&info.assembly, NULL, NULL);
	} else {
		MonoMethod *m = mono_method_get_last_managed ();
		MonoMethod *dest = m;

		mono_stack_walk_no_il (get_caller_no_reflection, &dest);
		if (!dest)
			dest = m;


		if (dest) {
			assembly = dest->klass->image->assembly;
			type_resolve = TRUE;
		} else {
			g_warning (G_STRLOC);
		}
	}

	if (assembly) {

		type = mono_reflection_get_type (assembly->image, &info, ignoreCase, &type_resolve);
	}

	if (!info.assembly.name && !type)
		type = mono_reflection_get_type (NULL, &info, ignoreCase, &type_resolve);

	if (assembly && !type && type_resolve) {
		type_resolve = FALSE;
		type = mono_reflection_get_type (assembly->image, &info, ignoreCase, &type_resolve);
	}

	mono_reflection_free_type_info (&info);
	g_free (temp_str);

	if (!type)
		return NULL;

	return mono_type_get_object (mono_domain_get (), type);
}
