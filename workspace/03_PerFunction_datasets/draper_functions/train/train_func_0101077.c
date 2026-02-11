mono_thread_abort (MonoObject *obj)
{


	if ((mono_runtime_unhandled_exception_policy_get () == MONO_UNHANDLED_POLICY_LEGACY) ||
			(obj->vtable->klass == mono_defaults.threadabortexception_class)) {
		mono_thread_exit ();
	} else {
		mono_invoke_unhandled_exception_hook (obj);
	}
}
