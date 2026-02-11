addnote(struct MFX *mfx, int pitch, int duration, int special)
{
	gn_ringtone_note *note;
	int scale;
	int lengths[] = { 4, 8, 16, 32, 64, 128 };

	int notes[] = { 0,  1,  2,  3,  4,  6,  7,  8,  9, 10, 11, 12 };


	if (mfx->ringtone->notes_count == GN_RINGTONE_MAX_NOTES-1)
		return;

	note = mfx->ringtone->notes + mfx->ringtone->notes_count;
	mfx->ringtone->notes_count++;

	if (pitch == 0) {

		note->note = 255;
	} else {
		pitch--;
		scale = pitch / 12;
		if (scale < 4)
			scale = 0;
		else if (scale > 7)
			scale = 3;
		else
			scale -= 4;
		note->note = 14 * (pitch / 12 - 4) + notes[pitch % 12];
	}

	if (duration < sizeof(lengths) / sizeof(lengths[0]))
		note->duration = lengths[duration];
	else
		note->duration = 4;
	if (special)
		note->duration *= 1.5;
}
