afGetVirtualFrameSize (AFfilehandle file, int trackid, int stretch3to4)
{
	if (!_af_filehandle_ok(file))
		return -1;

	Track *track = file->getTrack(trackid);
	if (!track)
		return -1;

	return _af_format_frame_size(&track->v, stretch3to4);
}
