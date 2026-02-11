process_frame (StackFrameInfo *info, MonoContext *ctx, gpointer user_data)
{
	ComputeFramesUserData *ud = user_data;
	StackFrame *frame;
	MonoMethod *method, *actual_method, *api_method;
	SeqPoint *sp;
	int flags = 0;

	if (info->type != FRAME_TYPE_MANAGED) {
		if (info->type == FRAME_TYPE_DEBUGGER_INVOKE) {

			if (ud->frames)
				((StackFrame*)g_slist_last (ud->frames)->data)->flags |= FRAME_FLAG_DEBUGGER_INVOKE;
		}
		return FALSE;
	}

	if (info->ji)
		method = jinfo_get_method (info->ji);
	else
		method = info->method;
	actual_method = info->actual_method;
	api_method = method;

	if (!method)
		return FALSE;

	if (!method || (method->wrapper_type && method->wrapper_type != MONO_WRAPPER_DYNAMIC_METHOD && method->wrapper_type != MONO_WRAPPER_MANAGED_TO_NATIVE))
		return FALSE;

	if (info->il_offset == -1) {

		if (ud->frames == NULL) {
			sp = find_prev_seq_point_for_native_offset (info->domain, method, info->native_offset, NULL);
			if (sp)
				info->il_offset = sp->il_offset;
		}
		if (info->il_offset == -1)
			info->il_offset = mono_debug_il_offset_from_address (method, info->domain, info->native_offset);
	}

	DEBUG (1, fprintf (log_file, "\tFrame: %s:%x(%x) %d\n", mono_method_full_name (method, TRUE), info->il_offset, info->native_offset, info->managed));

	if (method->wrapper_type == MONO_WRAPPER_MANAGED_TO_NATIVE) {
		if (!CHECK_PROTOCOL_VERSION (2, 17))

			return FALSE;
		api_method = mono_marshal_method_from_wrapper (method);
		if (!api_method)
			return FALSE;
		actual_method = api_method;
		flags |= FRAME_FLAG_NATIVE_TRANSITION;
	}

	frame = g_new0 (StackFrame, 1);
	frame->method = method;
	frame->actual_method = actual_method;
	frame->api_method = api_method;
	frame->il_offset = info->il_offset;
	frame->native_offset = info->native_offset;
	frame->flags = flags;
	frame->ji = info->ji;
	if (info->reg_locations)
		memcpy (frame->reg_locations, info->reg_locations, MONO_MAX_IREGS * sizeof (mgreg_t*));
	if (ctx) {
		frame->ctx = *ctx;
		frame->has_ctx = TRUE;
	}
	frame->domain = info->domain;

	ud->frames = g_slist_append (ud->frames, frame);

	return FALSE;
}
