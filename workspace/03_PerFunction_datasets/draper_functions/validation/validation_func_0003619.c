gf_isom_get_edit_list_type(GF_ISOFile *the_file, u32 trackNumber, s64 *mediaOffset)
{
	GF_EdtsEntry *ent;
	GF_TrackBox *trak;
	u32 count;
	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return 0;
	*mediaOffset = 0;
	if (!trak->editBox || !trak->editBox->editList) return 0;

	ent = gf_list_last(trak->editBox->editList->entryList);
	if (!ent || ent->segmentDuration) return 1;

	count = gf_list_count(trak->editBox->editList->entryList);

	if ((count==1) && (ent->mediaRate==1)) {
		*mediaOffset = - ent->mediaTime;
		return 0;
	} else if (count==2) {
		ent = gf_list_get(trak->editBox->editList->entryList, 0);

		if (ent->mediaRate==-1) {
			Double time = (Double) ent->segmentDuration;
			time /= trak->moov->mvhd->timeScale;
			time *= trak->Media->mediaHeader->timeScale;

			*mediaOffset = (s64) time;
			return 0;
		}
	}
	return 1;
}
