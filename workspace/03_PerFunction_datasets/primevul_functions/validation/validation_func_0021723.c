ms_escher_read_Blip (MSEscherState *state, MSEscherHeader *h)
{
	int offset = COMMON_HEADER_LEN + 16;
	guint32 inst = h->instance;
	gboolean needs_free, failure = FALSE;
	guint8 const *data;
	MSEscherBlip *blip = NULL;
	char const   *type = NULL;


	if (inst & 0x1) {
		offset += 16;
		inst &= (~0x1);
	}


	inst &= (~0x800);
	if (inst == 0x216 || inst == 0x3d4 || inst == 0x542) {
		guint8 const *tmp = ms_escher_get_data (state, h->offset + offset,
			META_FILE_HEADER_LEN, &needs_free);
		guint32 uncompressed_len = GSF_LE_GET_GUINT32 (tmp+0);
		guint32 compressed_len = GSF_LE_GET_GUINT32 (tmp+28);
		guint8  compress = tmp[32];
		guint8  filter	 = tmp[33];

		if (needs_free)
			g_free ((guint8*)tmp);
		offset += META_FILE_HEADER_LEN;

		if (inst == 0x216)
			type = "wmf";
		else if (inst == 0x3d4)
			type = "emf";
		else
			type = "pict";

		if (filter != 0xfe 	||
		    (unsigned)(h->len - offset) < compressed_len) {
			failure = TRUE;
			g_warning ("invalid metafile header %x, %u != %u;", filter,
				   (h->len - offset), compressed_len);
		} else {
			tmp = ms_escher_get_data (state, h->offset + offset,
				compressed_len, &needs_free);
			if (compress == 0) {
				uLongf len = uncompressed_len*4;
				guint8 *buffer = g_malloc (len);

				int res = uncompress (buffer, &len, tmp, compressed_len);
				if (res != Z_OK) {
					g_free (buffer);
					failure = TRUE;
					g_warning ("compression failure %d;", res);
				} else
					blip = ms_escher_blip_new (buffer,
						len, type, FALSE);
			} else if (compress == 0xfe) {
				blip = ms_escher_blip_new ((guint8 *)tmp, compressed_len,
					type, !needs_free);
				needs_free = FALSE;
			} else {
				failure = TRUE;
				g_warning ("Unknown compression type %hhx;", compress);
			}
			if (needs_free)
				g_free ((guint8*)tmp);
		}
	} else if (inst == 0x46a || inst == 0x6e0 || inst == 0x7a8) {
		if (inst == 0x46a)
			type = "jpeg";
		else if (inst == 0x6e0)
			type = "png";
		else
			type = "dib";
		offset++;
		data = ms_escher_get_data (state, h->offset + offset,
			h->len - offset, &needs_free);
		if (data)
			blip = ms_escher_blip_new ((guint8 *)data,
						   h->len - offset,
						   type, !needs_free);
		else
			failure = TRUE;
	} else {
		failure = TRUE;
		g_warning ("Don't know what to do with this image %x;", inst);
	}


	ms_container_add_blip (state->container, blip);
	return failure;
}
