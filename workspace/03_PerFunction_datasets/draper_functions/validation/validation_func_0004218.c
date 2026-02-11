x3ds_cb_0xB013(x3ds_global_data *global, x3ds_parent_data *parent)
{
	G3DObject *object;
#if 0
	gint32 i;
#endif
	gfloat x, y, z;

	object = parent->level_object;
	if(object == NULL) return FALSE;

	x = g3d_stream_read_float_le(global->stream);
	y = g3d_stream_read_float_le(global->stream);
	z = g3d_stream_read_float_le(global->stream);
	parent->nb -= 12;

#if DEBUG > 3
	g_debug("[3DS]: PIVOT: (%.2f,%.2f,%.2f)", x, y, z);
#endif

	return TRUE;
}
