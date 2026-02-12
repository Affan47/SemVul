jpeg_parse_exif_app1 (JpegExifContext *context, jpeg_saved_marker_ptr marker)
{
	guint i;
	guint ret = FALSE;
	guint offset;
	guint tags;
	guint endian = 0;
	const char leth[]  = {0x49, 0x49, 0x2a, 0x00};
	const char beth[]  = {0x4d, 0x4d, 0x00, 0x2a};


	if (marker->data_length < 4)
		goto out;


	if (memcmp (marker->data, "Exif", 4) != 0)
		goto out;


	if (marker->data_length < 32)
		goto out;


	for (i=0; i<16; i++) {

		if (memcmp (&marker->data[i], leth, 4) == 0) {
			endian = G_LITTLE_ENDIAN;
			ret = TRUE;
			break;
		}


		if (memcmp (&marker->data[i], beth, 4) == 0) {
			endian = G_BIG_ENDIAN;
			ret = TRUE;
			break;
		}
	}


	if (!ret)
		goto out;


	offset  = de_get32(&marker->data[i] + 4, endian);
	i = i + offset;


	{
	    const size_t new_i = i + 2;
	    if (new_i < i || new_i > marker->data_length) {
		    ret = FALSE;
		    goto out;
	    }


	    tags = de_get16(&marker->data[i], endian);
	    i = new_i;
	}


	{
	    const size_t new_i = i + tags * 12;
	    if (new_i < i || new_i > marker->data_length) {
		ret = FALSE;
		goto out;
	    }
	}


	while (tags--) {
		size_t new_i;


		guint tag   = de_get16(&marker->data[i + 0], endian);
		guint type  = de_get16(&marker->data[i + 2], endian);
		guint count = de_get32(&marker->data[i + 4], endian);


		if (tag == 0x112){


			if (type == 0x3 && count == 1) {
				guint short_value = de_get16(&marker->data[i + 8], endian);

				context->orientation = short_value <= 8 ? short_value : 0;
			} else if (type == 0x9 && count == 1) {
				guint long_value = de_get32(&marker->data[i + 8], endian);

				context->orientation = long_value <= 8 ? long_value : 0;
			}
		}

		new_i = i + 12;
		if (new_i < i || new_i > marker->data_length) {
			ret = FALSE;
			goto out;
		}
		i = new_i;
	}

out:
	return ret;
}
