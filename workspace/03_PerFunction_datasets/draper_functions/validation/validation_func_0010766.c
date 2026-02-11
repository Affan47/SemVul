predef_writable_counter (ImplVtable *vtable, MonoBoolean only_value, MonoCounterSample *sample)
{
	int cat_id = GPOINTER_TO_INT (vtable->arg);
	int id = cat_id >> 16;
	cat_id &= 0xffff;
	if (!only_value) {
		fill_sample (sample);
		sample->baseValue = 1;
	}
	sample->counterType = predef_counters [predef_categories [cat_id].first_counter + id].type;
	switch (cat_id) {
	case CATEGORY_EXC:
		switch (id) {
		case COUNTER_EXC_THROWN:
			sample->rawValue = mono_perfcounters->exceptions_thrown;
			return TRUE;
		}
		break;
	case CATEGORY_ASPNET:
		switch (id) {
		case COUNTER_ASPNET_REQ_Q:
			sample->rawValue = mono_perfcounters->aspnet_requests_queued;
			return TRUE;
		case COUNTER_ASPNET_REQ_TOTAL:
			sample->rawValue = mono_perfcounters->aspnet_requests;
			return TRUE;
		}
		break;
	case CATEGORY_THREADPOOL:
		switch (id) {
		case COUNTER_THREADPOOL_WORKITEMS:
			sample->rawValue = mono_perfcounters->threadpool_workitems;
			return TRUE;
		case COUNTER_THREADPOOL_IOWORKITEMS:
			sample->rawValue = mono_perfcounters->threadpool_ioworkitems;
			return TRUE;
		case COUNTER_THREADPOOL_THREADS:
			sample->rawValue = mono_perfcounters->threadpool_threads;
			return TRUE;
		case COUNTER_THREADPOOL_IOTHREADS:
			sample->rawValue = mono_perfcounters->threadpool_iothreads;
			return TRUE;
		}
		break;
	case CATEGORY_JIT:
		switch (id) {
		case COUNTER_JIT_BYTES:
			sample->rawValue = mono_perfcounters->jit_bytes;
			return TRUE;
		case COUNTER_JIT_METHODS:
			sample->rawValue = mono_perfcounters->jit_methods;
			return TRUE;
		case COUNTER_JIT_TIME:
			sample->rawValue = mono_perfcounters->jit_time;
			return TRUE;
		case COUNTER_JIT_BYTES_PSEC:
			sample->rawValue = mono_perfcounters->jit_bytes;
			return TRUE;
		case COUNTER_JIT_FAILURES:
			sample->rawValue = mono_perfcounters->jit_failures;
			return TRUE;
		}
		break;
	}
	return FALSE;
}
