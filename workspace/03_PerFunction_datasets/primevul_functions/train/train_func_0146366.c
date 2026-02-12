ves_icall_System_Reflection_Assembly_LoadPermissions (MonoReflectionAssembly *assembly,
	char **minimum, guint32 *minLength, char **optional, guint32 *optLength, char **refused, guint32 *refLength)
{
	MonoBoolean result = FALSE;
	MonoDeclSecurityEntry entry;


	if (mono_declsec_get_assembly_action (assembly->assembly, SECURITY_ACTION_REQMIN, &entry)) {
		*minimum = entry.blob;
		*minLength = entry.size;
		result = TRUE;
	}

	if (mono_declsec_get_assembly_action (assembly->assembly, SECURITY_ACTION_REQOPT, &entry)) {
		*optional = entry.blob;
		*optLength = entry.size;
		result = TRUE;
	}

	if (mono_declsec_get_assembly_action (assembly->assembly, SECURITY_ACTION_REQREFUSE, &entry)) {
		*refused = entry.blob;
		*refLength = entry.size;
		result = TRUE;
	}

	return result;
}
