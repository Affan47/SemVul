OTF_File_iofsl_getIndexEntries( OTF_File* file ) {
	OTF_File_iofsl *iofsl;
	size_t pos;

	if ( file == NULL || file->iofsl == NULL )
		return -1;

	iofsl = file->iofsl;
	if ( iofsl->id_str == NULL )
		return 0;

	if ( iofsl->indexfile == NULL )
		return -1;

	pos = iofsl->index_buffer_pos;

	rewind( iofsl->indexfile );

	do {
		IndexEntry* entry;
		int ret;


		if ( pos >= iofsl->index_buffer_length ) {
			IndexEntry* tmp = (IndexEntry*) realloc(
					iofsl->index_buffer,
					sizeof(IndexEntry) * ( iofsl->index_buffer_length
							+ OTF_IOFSL_INDEX_BUFFER_DEFAULTLENGTH ) );

			if ( tmp == NULL ) {
				OTF_Error( "ERROR in function %s, file: %s, line: %i:\n"
						"Failed to allocate %lu bytes of memory!",
						__FUNCTION__, __FILE__, __LINE__,
						sizeof(IndexEntry) *
						( iofsl->index_buffer_length + OTF_IOFSL_INDEX_BUFFER_DEFAULTLENGTH ) );
				return -1;
			}

			iofsl->index_buffer = tmp;

			iofsl->index_buffer_length += OTF_IOFSL_INDEX_BUFFER_DEFAULTLENGTH;
		}

		entry = &( iofsl->index_buffer[pos] );

		ret = OTF_File_iofsl_findIndexEntry( iofsl->indexfile, iofsl->id_str, NULL,
				&( entry->offset ), &( entry->length ), 0 );

		if ( ret == -1 ) {

			entry->offset = 0;
			entry->length = 0;
			break;
		}

		pos++;
	} while ( 1 );

	if ( pos == 0 ) {


		return -1;
	}

	return 0;
}
