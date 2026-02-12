int AVI_set_audio_track(avi_t *AVI, u32 track)
{

	if (track + 1 > AVI->anum) return(-1);


	AVI->aptr=track;
	return 0;
}
