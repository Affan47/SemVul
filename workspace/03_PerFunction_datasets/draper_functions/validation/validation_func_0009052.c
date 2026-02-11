alloc_handle (HandleData *handles, MonoObject *obj, gboolean track)
{
	gint slot, i;
	guint32 res;
	lock_handles (handles);
	if (!handles->size)
		handle_data_alloc_entries (handles);
	i = handle_data_next_unset (handles);
	if (i == -1 && handles->slot_hint != 0)
		i = handle_data_first_unset (handles);
	if (i == -1) {
		handle_data_grow (handles, track);
		i = 0;
	}
	slot = handles->slot_hint * BITMAP_SIZE + i;
	occupy_slot (handles, slot);
	handles->entries [slot] = NULL;
	if (MONO_GC_HANDLE_TYPE_IS_WEAK (handles->type)) {

		handles->domain_ids [slot] = (obj ? mono_object_get_domain (obj) : mono_domain_get ())->domain_id;
		if (obj)
			mono_gc_weak_link_add (&(handles->entries [slot]), obj, track);
	} else {
		handles->entries [slot] = obj;
	}

#ifndef DISABLE_PERFCOUNTERS
	mono_perfcounters->gc_num_handles++;
#endif
	unlock_handles (handles);
	res = MONO_GC_HANDLE (slot, handles->type);
	mono_profiler_gc_handle (MONO_PROFILER_GC_HANDLE_CREATED, handles->type, res, obj);
	return res;
}
