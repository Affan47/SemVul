gfxr_interpreter_get_resources(gfx_resstate_t *state, gfx_resource_type_t type,
			       int version, int *entries_nr, void *internal)
{
	resource_mgr_t *resmgr = (resource_mgr_t *) state->misc_payload;
	int restype;
	int *resources;
	int count = 0;
	int top = sci_max_resource_nr[version] + 1;
	int i;
	switch (type) {

	case GFX_RESOURCE_TYPE_VIEW: restype = sci_view;
		break;

	case GFX_RESOURCE_TYPE_PIC: restype = sci_pic;
		break;

	case GFX_RESOURCE_TYPE_CURSOR: restype = sci_cursor;
		break;

	case GFX_RESOURCE_TYPE_FONT: restype = sci_font;
		break;

	default:
		GFX_DEBUG("Unsupported resource %d\n", type);
		return NULL;

	}

	resources = (int*)sci_malloc(sizeof(int) * top);

	for (i = 0; i < top; i++)
		if (scir_test_resource(resmgr, restype, i))
			resources[count++] = i;

	*entries_nr = count;

	return resources;
}
