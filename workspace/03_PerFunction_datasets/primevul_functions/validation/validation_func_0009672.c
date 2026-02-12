mono_free_method  (MonoMethod *method)
{
	if (mono_profiler_get_events () & MONO_PROFILE_METHOD_EVENTS)
		mono_profiler_method_free (method);


	if (mono_profiler_get_events () != MONO_PROFILE_NONE)
		return;

	if (method->signature) {


	}

	if (method->dynamic) {
		MonoMethodWrapper *mw = (MonoMethodWrapper*)method;
		int i;

		mono_marshal_free_dynamic_wrappers (method);

		mono_image_property_remove (method->klass->image, method);

		g_free ((char*)method->name);
		if (mw->header) {
			g_free ((char*)mw->header->code);
			for (i = 0; i < mw->header->num_locals; ++i)
				g_free (mw->header->locals [i]);
			g_free (mw->header->clauses);
			g_free (mw->header);
		}
		g_free (mw->method_data);
		g_free (method->signature);
		g_free (method);
	}
}
