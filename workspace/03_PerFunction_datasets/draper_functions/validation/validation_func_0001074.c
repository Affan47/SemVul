mpg123_seek(mpg123_handle *mh, off_t sampleoff, int whence)
{
	int b;
	off_t pos;
	ALIGNCHECK(mh);
	pos = mpg123_tell(mh);


	if(pos < 0 && whence != SEEK_SET)
	{
		if(mh != NULL) mh->err = MPG123_NO_RELSEEK;
		return MPG123_ERR;
	}
	if((b=init_track(mh)) < 0) return b;
	switch(whence)
	{
		case SEEK_CUR: pos += sampleoff; break;
		case SEEK_SET: pos  = sampleoff; break;
		case SEEK_END:

			if(mh->track_frames < 1 && (mh->rdat.flags & READER_SEEKABLE))
			mpg123_scan(mh);
#ifdef GAPLESS
			if(mh->end_os > 0) pos = SAMPLE_ADJUST(mh->end_os) - sampleoff;
#else
			if(mh->track_frames > 0) pos = SAMPLE_ADJUST(frame_outs(mh, mh->track_frames)) - sampleoff;
#endif
			else
			{
				mh->err = MPG123_NO_SEEK_FROM_END;
				return MPG123_ERR;
			}
		break;
		default: mh->err = MPG123_BAD_WHENCE; return MPG123_ERR;
	}
	if(pos < 0) pos = 0;

	frame_set_seek(mh, SAMPLE_UNADJUST(pos));
	pos = do_the_seek(mh);
	if(pos < 0) return pos;

	return mpg123_tell(mh);
}
