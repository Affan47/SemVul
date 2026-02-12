static guint32 WINAPI start_wrapper_internal(void *data)
{
	struct StartInfo *start_info=(struct StartInfo *)data;
	guint32 (*start_func)(void *);
	void *start_arg;
	gsize tid;


	MonoInternalThread *internal = start_info->obj->internal_thread;
	MonoObject *start_delegate = start_info->delegate;
	MonoDomain *domain = start_info->obj->obj.vtable->domain;

	THREAD_DEBUG (g_message ("%s: (%"G_GSIZE_FORMAT") Start wrapper", __func__, GetCurrentThreadId ()));


	tid=internal->tid;

	SET_CURRENT_OBJECT (internal);

	mono_monitor_init_tls ();


	mono_thread_push_appdomain_ref (domain);

	if (!mono_domain_set (domain, FALSE)) {


		mono_thread_pop_appdomain_ref ();
		return 0;
	}

	start_func = start_info->func;
	start_arg = start_info->start_arg;


	thread_adjust_static_data (internal);
	init_root_domain_thread (internal, start_info->obj);


	mono_thread_new_init (tid, &tid, start_func);
	internal->stack_ptr = &tid;

	LIBGC_DEBUG (g_message ("%s: (%"G_GSIZE_FORMAT",%d) Setting thread stack to %p", __func__, GetCurrentThreadId (), getpid (), thread->stack_ptr));

	THREAD_DEBUG (g_message ("%s: (%"G_GSIZE_FORMAT") Setting current_object_key to %p", __func__, GetCurrentThreadId (), internal));


	if (internal->apartment_state == ThreadApartmentState_Unknown)
		internal->apartment_state = ThreadApartmentState_MTA;

	mono_thread_init_apartment_state ();

	if(internal->start_notify!=NULL) {


		ReleaseSemaphore (internal->start_notify, 1, NULL);
	}

	mono_threads_lock ();
	mono_g_hash_table_remove (thread_start_args, start_info->obj);
	mono_threads_unlock ();

	mono_thread_set_execution_context (start_info->obj->ec_to_set);
	start_info->obj->ec_to_set = NULL;

	g_free (start_info);
	THREAD_DEBUG (g_message ("%s: start_wrapper for %"G_GSIZE_FORMAT, __func__,
							 internal->tid));


	mono_profiler_thread_start (tid);


	if (start_func) {
		start_func (start_arg);
	} else {
		void *args [1];
		g_assert (start_delegate != NULL);
		args [0] = start_arg;

		mono_runtime_delegate_invoke (start_delegate, args, NULL);
	}


	THREAD_DEBUG (g_message ("%s: (%"G_GSIZE_FORMAT") Start wrapper terminating", __func__, GetCurrentThreadId ()));

	thread_cleanup (internal);


	mono_thread_cleanup_apartment_state ();


	SET_CURRENT_OBJECT (NULL);
	mono_domain_unset ();

	return(0);
}
