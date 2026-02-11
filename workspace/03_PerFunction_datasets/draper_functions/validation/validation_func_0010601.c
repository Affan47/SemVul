mono_gc_alloc_array (MonoVTable *vtable, size_t size, uintptr_t max_length, uintptr_t bounds_size)
{
	MonoArray *arr;
	MonoArrayBounds *bounds;

#ifndef DISABLE_CRITICAL_REGION
	TLAB_ACCESS_INIT;
	ENTER_CRITICAL_REGION;
	arr = mono_gc_try_alloc_obj_nolock (vtable, size);
	if (arr) {

		arr->max_length = max_length;

		bounds = (MonoArrayBounds*)((char*)arr + size - bounds_size);
		arr->bounds = bounds;
		EXIT_CRITICAL_REGION;
		return arr;
	}
	EXIT_CRITICAL_REGION;
#endif

	LOCK_GC;

	arr = mono_gc_alloc_obj_nolock (vtable, size);
	if (G_UNLIKELY (!arr)) {
		UNLOCK_GC;
		return mono_gc_out_of_memory (size);
	}

	arr->max_length = max_length;

	bounds = (MonoArrayBounds*)((char*)arr + size - bounds_size);
	arr->bounds = bounds;

	UNLOCK_GC;

	return arr;
}
