ignore_frame (MonoMethod *method)
{
	MonoClass *klass = method->klass;

	if (method->wrapper_type != MONO_WRAPPER_NONE)
		return TRUE;


	if (klass->image ) {
		if (strcmp (klass->image->assembly_name, "mscorlib") == 0)
			return TRUE;
		else if (strcmp (klass->image->assembly_name, "System") == 0)
			return TRUE;
		else if (strncmp (klass->image->assembly_name, "Mono.", 5) == 0)
			return TRUE;
		else if (strncmp (klass->image->assembly_name, "System.", 7) == 0)
			return TRUE;
		else if (strcmp (klass->image->assembly_name, "PEAPI") == 0)
			return TRUE;
	}

	return FALSE;
}
