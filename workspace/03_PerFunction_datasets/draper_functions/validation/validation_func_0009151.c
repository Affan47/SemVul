afWriteFrames (AFfilehandle file, int trackid, const void *samples,
	int nvframes2write)
{
	SharedPtr<Module> firstmod;
	SharedPtr<Chunk> userc;
	int bytes_per_vframe;
	AFframecount vframe;

	if (!_af_filehandle_ok(file))
		return -1;

	if (!file->checkCanWrite())
		return -1;

	Track *track = file->getTrack(trackid);
	if (!track)
		return -1;

	if (track->ms->isDirty() && track->ms->setup(file, track) == AF_FAIL)
		return -1;

	if (!track->ms->fileModuleHandlesSeeking() &&
		file->m_seekok &&
		file->m_fh->seek(track->fpos_next_frame, File::SeekFromBeginning) !=
			track->fpos_next_frame)
	{
		_af_error(AF_BAD_LSEEK, "unable to position write pointer at next frame");
		return -1;
	}

	bytes_per_vframe = _af_format_frame_size(&track->v, true);

	firstmod = track->ms->modules().front();
	userc = track->ms->chunks().front();

	track->filemodhappy = true;

	vframe = 0;
#ifdef UNLIMITED_CHUNK_NVFRAMES


	if (!trk->ms->mustUseAtomicNVFrames())
	{
		userc->buffer = (char *) samples;
		userc->frameCount = nvframes2write;

		firstmod->runPush();


		if (trk->filemodhappy)
			vframe += userc->frameCount;
	}
	else
#else

	assert(track->ms->mustUseAtomicNVFrames());
#endif
	{
		while (vframe < nvframes2write)
		{
			userc->buffer = (char *) samples + bytes_per_vframe * vframe;
			if (vframe <= nvframes2write - _AF_ATOMIC_NVFRAMES)
				userc->frameCount = _AF_ATOMIC_NVFRAMES;
			else
				userc->frameCount = nvframes2write - vframe;

			firstmod->runPush();

			if (!track->filemodhappy)
				break;

			vframe += userc->frameCount;
		}
	}

	track->nextvframe += vframe;
	track->totalvframes += vframe;

	return vframe;
}
