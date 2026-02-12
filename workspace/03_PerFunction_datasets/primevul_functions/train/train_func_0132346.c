AFframecount afSeekFrame (AFfilehandle file, int trackid, AFframecount frame)
{
	_Track	*track;

	if (!_af_filehandle_ok(file))
		return -1;

	if (!_af_filehandle_can_read(file))
		return -1;

	if ((track = _af_filehandle_get_track(file, trackid)) == NULL)
		return -1;

	if (track->ms->isDirty() && track->ms->setup(file, track) == AF_FAIL)
		return -1;

	if (frame < 0)
		return track->nextvframe;


	if (frame == track->nextvframe)
		return track->nextvframe;


	if (track->totalvframes != -1)
		if (frame > track->totalvframes)
			frame = track->totalvframes - 1;


	track->nextvframe = frame;

	if (track->ms->setup(file, track) == AF_FAIL)
		return -1;

	return track->nextvframe;
}
