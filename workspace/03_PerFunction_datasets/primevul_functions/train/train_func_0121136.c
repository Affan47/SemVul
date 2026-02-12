exif_data_save_data_content (ExifData *data, ExifContent *ifd,
			     unsigned char **d, unsigned int *ds,
			     unsigned int offset)
{
	unsigned int j, n_ptr = 0, n_thumb = 0;
	ExifIfd i;
	unsigned char *t;
	unsigned int ts;

	if (!data || !data->priv || !ifd || !d || !ds)
		return;

	for (i = 0; i < EXIF_IFD_COUNT; i++)
		if (ifd == data->ifd[i])
			break;
	if (i == EXIF_IFD_COUNT)
		return;


	switch (i) {
	case EXIF_IFD_0:


		if (data->ifd[EXIF_IFD_EXIF]->count ||
		    data->ifd[EXIF_IFD_INTEROPERABILITY]->count)
			n_ptr++;


		if (data->ifd[EXIF_IFD_GPS]->count)
			n_ptr++;

		break;
	case EXIF_IFD_1:
		if (data->size)
			n_thumb = 2;
		break;
	case EXIF_IFD_EXIF:
		if (data->ifd[EXIF_IFD_INTEROPERABILITY]->count)
			n_ptr++;
	default:
		break;
	}


	ts = *ds + (2 + (ifd->count + n_ptr + n_thumb) * 12 + 4);
	t = exif_mem_realloc (data->priv->mem, *d, ts);
	if (!t) {
		EXIF_LOG_NO_MEMORY (data->priv->log, "ExifData", ts);
	  	return;
	}
	*d = t;
	*ds = ts;


	exif_set_short (*d + 6 + offset, data->priv->order,
			(ExifShort) (ifd->count + n_ptr + n_thumb));
	offset += 2;


	exif_log (data->priv->log, EXIF_LOG_CODE_DEBUG, "ExifData",
		  "Saving %i entries (IFD '%s', offset: %i)...",
		  ifd->count, exif_ifd_get_name (i), offset);
	for (j = 0; j < ifd->count; j++) {
		if (ifd->entries[j]) {
			exif_data_save_data_entry (data, ifd->entries[j], d, ds,
				offset + 12 * j);
		}
	}

	offset += 12 * ifd->count;


	switch (i) {
	case EXIF_IFD_0:


		if (data->ifd[EXIF_IFD_EXIF]->count ||
		    data->ifd[EXIF_IFD_INTEROPERABILITY]->count) {
			exif_set_short (*d + 6 + offset + 0, data->priv->order,
					EXIF_TAG_EXIF_IFD_POINTER);
			exif_set_short (*d + 6 + offset + 2, data->priv->order,
					EXIF_FORMAT_LONG);
			exif_set_long  (*d + 6 + offset + 4, data->priv->order,
					1);
			exif_set_long  (*d + 6 + offset + 8, data->priv->order,
					*ds - 6);
			exif_data_save_data_content (data,
						     data->ifd[EXIF_IFD_EXIF], d, ds, *ds - 6);
			offset += 12;
		}


		if (data->ifd[EXIF_IFD_GPS]->count) {
			exif_set_short (*d + 6 + offset + 0, data->priv->order,
					EXIF_TAG_GPS_INFO_IFD_POINTER);
			exif_set_short (*d + 6 + offset + 2, data->priv->order,
					EXIF_FORMAT_LONG);
			exif_set_long  (*d + 6 + offset + 4, data->priv->order,
					1);
			exif_set_long  (*d + 6 + offset + 8, data->priv->order,
					*ds - 6);
			exif_data_save_data_content (data,
						     data->ifd[EXIF_IFD_GPS], d, ds, *ds - 6);
			offset += 12;
		}

		break;
	case EXIF_IFD_EXIF:


		if (data->ifd[EXIF_IFD_INTEROPERABILITY]->count) {
			exif_set_short (*d + 6 + offset + 0, data->priv->order,
					EXIF_TAG_INTEROPERABILITY_IFD_POINTER);
			exif_set_short (*d + 6 + offset + 2, data->priv->order,
					EXIF_FORMAT_LONG);
			exif_set_long  (*d + 6 + offset + 4, data->priv->order,
					1);
			exif_set_long  (*d + 6 + offset + 8, data->priv->order,
					*ds - 6);
			exif_data_save_data_content (data,
						     data->ifd[EXIF_IFD_INTEROPERABILITY], d, ds,
						     *ds - 6);
			offset += 12;
		}

		break;
	case EXIF_IFD_1:


		if (data->size) {


			exif_set_short (*d + 6 + offset + 0, data->priv->order,
					EXIF_TAG_JPEG_INTERCHANGE_FORMAT);
			exif_set_short (*d + 6 + offset + 2, data->priv->order,
					EXIF_FORMAT_LONG);
			exif_set_long  (*d + 6 + offset + 4, data->priv->order,
					1);
			exif_set_long  (*d + 6 + offset + 8, data->priv->order,
					*ds - 6);
			ts = *ds + data->size;
			t = exif_mem_realloc (data->priv->mem, *d, ts);
			if (!t) {
				EXIF_LOG_NO_MEMORY (data->priv->log, "ExifData",
						    ts);
			  	return;
			}
			*d = t;
			*ds = ts;
			memcpy (*d + *ds - data->size, data->data, data->size);
			offset += 12;


			exif_set_short (*d + 6 + offset + 0, data->priv->order,
					EXIF_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH);
			exif_set_short (*d + 6 + offset + 2, data->priv->order,
					EXIF_FORMAT_LONG);
			exif_set_long  (*d + 6 + offset + 4, data->priv->order,
					1);
			exif_set_long  (*d + 6 + offset + 8, data->priv->order,
					data->size);
			offset += 12;
		}

		break;
	default:
		break;
	}


	qsort (*d + 6 + offset - (ifd->count + n_ptr + n_thumb) * 12,
	       (ifd->count + n_ptr + n_thumb), 12,
	       (data->priv->order == EXIF_BYTE_ORDER_INTEL) ? cmp_func_intel : cmp_func_motorola);


	if (i == EXIF_IFD_0 && (data->ifd[EXIF_IFD_1]->count ||
				data->size)) {


		exif_set_long (*d + 6 + offset, data->priv->order, *ds - 6);
		exif_data_save_data_content (data, data->ifd[EXIF_IFD_1], d, ds,
					     *ds - 6);
	} else
		exif_set_long (*d + 6 + offset, data->priv->order, 0);
}
