load_editor_sounds()
{
  int i;

  if (InitSound() < 0)
    return -1;


  for(i = 0; i < NUM_SOUND_EFFECTS; i++)
    {
      char *filename = szSoundEffects[i];
      log_info("Loading sound %s [%d]", filename, i);


      SDL_RWops* rwops;
      rwops = find_resource_as_rwops(filename);
      if (rwops != NULL)
	CreateBufferFromWaveFile_RW(rwops, 1, i);
      else
	log_error("Cannot load sound effect %s, from resources or from %s",
		  filename, paths_getpkgdatadir());
    }
  return 1;
}
