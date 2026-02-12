exif_data_save_data_entry (ExifData *data, ExifEntry *e,
			   unsigned char **d, unsigned int *ds,
			   unsigned int offset)
{
	unsigned int doff, s;
	unsigned int ts;

	if (!data || !data->priv)
		return;


	exif_set_short (*d + 6 + offset + 0,
			data->priv->order, (ExifShort) e->tag);
	exif_set_short (*d + 6 + offset + 2,
			data->priv->order, (ExifShort) e->format);

	if (!(data->priv->options & EXIF_DATA_OPTION_DONT_CHANGE_MAKER_NOTE)) {

		if ((e->tag == EXIF_TAG_MAKER_NOTE) && data->priv->md) {

			exif_mem_free (data->priv->mem, e->data);
			e->data = NULL;
			e->size = 0;
			exif_mnote_data_set_offset (data->priv->md, *ds - 6);
			exif_mnote_data_save (data->priv->md, &e->data, &e->size);
			e->components = e->size;
			if (exif_format_get_size (e->format) != 1) {


				e->format = EXIF_FORMAT_UNDEFINED;
			}
		}
	}

	exif_set_long  (*d + 6 + offset + 4,
			data->priv->order, e->components);


	s = exif_format_get_size (e->format) * e->components;
	if (s > 4) {
		unsigned char *t;
		doff = *ds - 6;
		ts = *ds + s;


		if (s & 1)
			ts++;
		t = exif_mem_realloc (data->priv->mem, *d, ts);
		if (!t) {
			EXIF_LOG_NO_MEMORY (data->priv->log, "ExifData", ts);
		  	return;
		}
		*d = t;
		*ds = ts;
		exif_set_long (*d + 6 + offset + 8, data->priv->order, doff);
		if (s & 1)
			*(*d + *ds - 1) = '\0';

	} else
		doff = offset + 8;


	if (e->data) {
		memcpy (*d + 6 + doff, e->data, s);
	} else {
		memset (*d + 6 + doff, 0, s);
	}
	if (s < 4)
		memset (*d + 6 + doff + s, 0, (4 - s));
}
