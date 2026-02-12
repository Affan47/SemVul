static BOOL rdp_read_sound_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	UINT16 soundFlags;

	if (length < 8)
		return FALSE;

	Stream_Read_UINT16(s, soundFlags);
	Stream_Seek_UINT16(s);
	settings->SoundBeepsEnabled = (soundFlags & SOUND_BEEPS_FLAG) ? TRUE : FALSE;
	return TRUE;
}
