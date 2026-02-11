restore_cd (int num, uae_u8 *src)
{
	uae_u32 flags;
	TCHAR *s;

	if (num >= MAX_TOTAL_SCSI_DEVICES)
		return NULL;
	flags = restore_u32 ();
	s = restore_path (SAVESTATE_PATH_CD);
	int type = restore_u32 ();
	restore_u32 ();
	if (flags & 4) {
		if (currprefs.cdslots[num].name[0] == 0 || zfile_exists (s)) {
			_tcscpy (changed_prefs.cdslots[num].name, s);
			_tcscpy (currprefs.cdslots[num].name, s);
		}
		changed_prefs.cdslots[num].type = currprefs.cdslots[num].type = type;
	}
	if (flags & 8) {
		restore_u32 ();
		for (int i = 0; i < SUBQ_SIZE; i++)
			play_qcode[num][i] = restore_u8 ();
		play_end_pos[num] = restore_u32 ();
	}
	return src;
}
