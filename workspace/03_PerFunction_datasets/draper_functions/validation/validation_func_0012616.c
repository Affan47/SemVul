LoadAndFadeInBackgroundMusic(void)
{
#ifndef HAVE_LIBSDL_MIXER
	return;
#else

	char fpath[2048];
	char filename_raw[2048];

	if (!sound_on)
		return;

	if (filename_raw == SILENCE)
	{


		Mix_HaltMusic();
		return;
	}


	if (Loaded_MOD_Files[0] != NULL) {
		Mix_FreeMusic(Loaded_MOD_Files[0]);
		Loaded_MOD_Files[0] = NULL;
	}

	strcpy(filename_raw, "music/");
	strcat(filename_raw, NewMusicTargetFileName);
	find_file(filename_raw, SOUND_DIR, fpath, 0);
	Loaded_MOD_Files[0] = Mix_LoadMUS(fpath);
	if (Loaded_MOD_Files[0] == NULL) {
		DebugPrintf(0, "The music file %s could not be loaded!\n", NewMusicTargetFileName);
		return;
	} else
		DebugPrintf(1, "\nSuccessfully loaded file %s.", fpath);

	Mix_PlayMusic(Loaded_MOD_Files[0], -1);

	Mix_VolumeMusic((int)rintf(GameConfig.Current_BG_Music_Volume * MIX_MAX_VOLUME));

#endif
}
