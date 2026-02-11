parse_mtrk_header(smf_track_t *track)
{
	struct chunk_header_struct *mtrk;


	assert(sizeof(struct chunk_header_struct) == 8);
	assert(track->smf != NULL);

	mtrk = next_chunk(track->smf);

	if (mtrk == NULL)
		return (-1);

	if (!chunk_signature_matches(mtrk, "MTrk")) {
		g_warning("SMF warning: Expected MTrk signature, got %c%c%c%c instead; ignoring this chunk.",
				mtrk->id[0], mtrk->id[1], mtrk->id[2], mtrk->id[3]);

		return (-2);
	}

	track->file_buffer = mtrk;
	track->file_buffer_length = sizeof(struct chunk_header_struct) + ntohl(mtrk->length);
	track->next_event_offset = sizeof(struct chunk_header_struct);

	return (0);
}
