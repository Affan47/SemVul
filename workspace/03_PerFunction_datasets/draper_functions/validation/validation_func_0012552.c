get_shared_inst (MonoGenericInst *inst, MonoGenericInst *shared_inst, MonoGenericContainer *container, gboolean all_vt, gboolean gsharedvt)
{
	MonoGenericInst *res;
	MonoType **type_argv;
	int i;

	type_argv = g_new0 (MonoType*, inst->type_argc);
	for (i = 0; i < inst->type_argc; ++i) {
		if (!all_vt && (MONO_TYPE_IS_REFERENCE (inst->type_argv [i]) || inst->type_argv [i]->type == MONO_TYPE_VAR || inst->type_argv [i]->type == MONO_TYPE_MVAR)) {
			type_argv [i] = shared_inst->type_argv [i];
		} else if (all_vt) {
			type_argv [i] = get_gsharedvt_type (shared_inst->type_argv [i]);
		} else if (gsharedvt) {
			type_argv [i] = get_gsharedvt_type (shared_inst->type_argv [i]);
		} else {
			type_argv [i] = inst->type_argv [i];
		}
	}

	res = mono_metadata_get_generic_inst (inst->type_argc, type_argv);
	g_free (type_argv);
	return res;
}
