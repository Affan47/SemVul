mono_ArgIterator_IntGetNextArgT (MonoArgIterator *iter, MonoType *type)
{
	guint32 i, arg_size;
	gint32 align;
	MonoTypedRef res;
	MONO_ARCH_SAVE_REGS;

	i = iter->sig->sentinelpos + iter->next_arg;

	g_assert (i < iter->sig->param_count);

	while (i < iter->sig->param_count) {
		if (!mono_metadata_type_equal (type, iter->sig->params [i]))
			continue;
		res.type = iter->sig->params [i];
		res.klass = mono_class_from_mono_type (res.type);

		res.value = iter->args;
		arg_size = mono_type_stack_size (res.type, &align);
		iter->args = (char*)iter->args + arg_size;
		iter->next_arg++;

		return res;
	}


	res.type = NULL;
	res.value = NULL;
	res.klass = NULL;
	return res;
}
