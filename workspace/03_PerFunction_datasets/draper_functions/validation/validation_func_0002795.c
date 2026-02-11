push_object (GCObject *obj)
{
	ScanData *data;
	obj = bridge_object_forward (obj);

#if DUMP_GRAPH
	printf ("\t= pushing %p %s -> ", obj, safe_name_bridge (obj));
#endif


	if (is_opaque_object (obj)) {
#if DUMP_GRAPH
		printf ("opaque\n");
#endif
		return;
	}

	data = find_data (obj);


	if (data && data->state != INITIAL) {
#if DUMP_GRAPH
		printf ("already marked\n");
#endif
		return;
	}


	if (!data && sgen_object_is_live (obj)) {
#if DUMP_GRAPH
		printf ("alive\n");
#endif
		return;
	}

#if DUMP_GRAPH
	printf ("pushed!\n");
#endif

	if (!data)
		data = create_data (obj);
	g_assert (data->state == INITIAL);
	g_assert (data->index == -1);
	dyn_array_ptr_push (&scan_stack, data);
}
