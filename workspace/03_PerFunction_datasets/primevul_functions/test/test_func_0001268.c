GF_Err gf_isom_begin_hint_sample(GF_ISOFile *the_file, u32 trackNumber, u32 HintDescriptionIndex, u32 TransmissionTime)
{
	GF_TrackBox *trak;
	u32 descIndex, dataRefIndex;
	GF_HintSample *samp;
	GF_HintSampleEntryBox *entry;
	GF_Err e;

	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak || !IsHintTrack(trak)) return GF_BAD_PARAM;


	if (trak->Media->information->sampleTable->TimeToSample->w_LastDTS > TransmissionTime) return GF_BAD_PARAM;


	descIndex = HintDescriptionIndex;
	if (!HintDescriptionIndex) {
		descIndex = trak->Media->information->sampleTable->currentEntryIndex;
	}
	e = Media_GetSampleDesc(trak->Media, descIndex, (GF_SampleEntryBox **) &entry, &dataRefIndex);
	if (e) return e;
	if (!entry || !dataRefIndex) return GF_BAD_PARAM;

	if (entry->hint_sample) return GF_BAD_PARAM;
	trak->Media->information->sampleTable->currentEntryIndex = descIndex;


	samp = gf_isom_hint_sample_new(entry->type);
	if (!samp) return GF_NOT_SUPPORTED;


	samp->TransmissionTime = TransmissionTime;

	entry->hint_sample = samp;
	return GF_OK;
}
