cuesheet_set_track_(FLAC__StreamMetadata *object, FLAC__StreamMetadata_CueSheet_Track *dest, const FLAC__StreamMetadata_CueSheet_Track *src, FLAC__bool copy)
{
	FLAC__StreamMetadata_CueSheet_Index *save;

	FLAC__ASSERT(0 != object);
	FLAC__ASSERT(0 != dest);
	FLAC__ASSERT(0 != src);
	FLAC__ASSERT(object->type == FLAC__METADATA_TYPE_CUESHEET);
	FLAC__ASSERT((0 != src->indices && src->num_indices > 0) || (0 == src->indices && src->num_indices == 0));

	save = dest->indices;


	if(copy) {
		if(!copy_track_(dest, src))
			return false;
	}
	else {
		*dest = *src;
	}

	if(0 != save)
		free(save);

	cuesheet_calculate_length_(object);
	return true;
}
