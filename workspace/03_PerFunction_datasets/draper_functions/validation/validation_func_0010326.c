_sm_deallocate (seg_manager_t* self, int seg, int recursive)
{
	mem_obj_t *mobj;
	VERIFY ( sm_check (self, seg), "invalid seg id" );

	mobj = self->heap[seg];
	int_hash_map_remove_value( self->id_seg_map, mobj->segmgr_id );

	switch (mobj->type) {

	case MEM_OBJ_SCRIPT:
		sm_free_script ( mobj );

		mobj->data.script.buf = NULL;
		if (recursive && mobj->data.script.locals_segment)
			_sm_deallocate(self, mobj->data.script.locals_segment,
				       recursive);
		break;

	case MEM_OBJ_LOCALS:
		sci_free(mobj->data.locals.locals);
		mobj->data.locals.locals = NULL;
		break;

	case MEM_OBJ_DYNMEM:
		if (mobj->data.dynmem.buf)
			sci_free(mobj->data.dynmem.buf);
		mobj->data.dynmem.buf = NULL;
		break;
	case MEM_OBJ_SYS_STRINGS:
		sys_string_free_all(&(mobj->data.sys_strings));
		break;
	case MEM_OBJ_STACK:
		sci_free(mobj->data.stack.entries);
		mobj->data.stack.entries = NULL;
		break;
	case MEM_OBJ_LISTS:
		sci_free(mobj->data.lists.table);
		mobj->data.lists.table = NULL;
		mobj->data.lists.entries_nr = mobj->data.lists.max_entry = 0;
		break;
	case MEM_OBJ_NODES:
		sci_free(mobj->data.nodes.table);
		mobj->data.nodes.table = NULL;
		mobj->data.nodes.entries_nr = mobj->data.nodes.max_entry = 0;
		break;
	case MEM_OBJ_CLONES:
		sci_free(mobj->data.clones.table);
		mobj->data.clones.table = NULL;
		mobj->data.clones.entries_nr = mobj->data.clones.max_entry = 0;
		break;
	case MEM_OBJ_HUNK:
		sci_free(mobj->data.hunks.table);
		mobj->data.hunks.table = NULL;
		mobj->data.hunks.entries_nr = mobj->data.hunks.max_entry = 0;
		break;
	case MEM_OBJ_RESERVED:
		sci_free(mobj->data.reserved);
		break;
	default:
		fprintf(stderr, "Deallocating segment type %d not supported!\n",
			mobj->type);
		BREAKPOINT();
	}

	free(mobj);
	self->heap[seg] = NULL;

	return 1;
}
