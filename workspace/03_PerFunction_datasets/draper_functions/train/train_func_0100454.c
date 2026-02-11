debrief_pause()
{
	if (Debriefing_paused)
		return;

	Debriefing_paused = 1;

	if (Briefing_music_handle >= 0) {
		audiostream_pause(Briefing_music_handle);
	}

	if ((Stage_voice < 0) || (Stage_voice > Num_debrief_stages) || (Debrief_voices[Stage_voice] < 0))
		return;

	audiostream_pause(Debrief_voices[Stage_voice]);

	fsspeech_pause(true);
}
