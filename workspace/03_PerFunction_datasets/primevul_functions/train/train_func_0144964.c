jpeg_parse_exif_app2_segment (JpegExifContext *context, jpeg_saved_marker_ptr marker)
{
	guint ret = FALSE;
	guint sequence_number;
	guint number_of_chunks;
	guint chunk_size;
	guint offset;


	if (marker->data_length < 16)
		goto out;


	if (memcmp (marker->data, "ICC_PROFILE\0", 12) != 0)
		goto out;


	sequence_number = marker->data[12];
	number_of_chunks = marker->data[13];


	if (sequence_number == 0)
		goto out;


	if (sequence_number > number_of_chunks)
		goto out;


	chunk_size = marker->data_length - 14;
	offset = (sequence_number - 1) * 0xffef;


	if (number_of_chunks == 1) {
		if (context->icc_profile_size_allocated > 0)
			goto out;
		context->icc_profile_size = chunk_size;
		context->icc_profile_size_allocated = chunk_size;
		context->icc_profile = g_new (gchar, chunk_size);

		memcpy (context->icc_profile, marker->data + 14, chunk_size);
		goto out;
	}


	if (context->icc_profile_size_allocated == 0) {
		context->icc_profile_size_allocated = number_of_chunks * 0xffff;
		context->icc_profile = g_new0 (gchar, number_of_chunks * 0xffff);
	}


	if (offset + chunk_size > context->icc_profile_size_allocated)
		goto out;


	memcpy (context->icc_profile + offset, marker->data + 14, chunk_size);


	context->icc_profile_size += chunk_size;


	ret = TRUE;
out:
	return ret;
}
