reset_rtpprintf(void)
{
	log_lock();
	if(_rtpfile) {
		if(_rtpfile != stdout)
			fclose(_rtpfile);
		_rtpfile = NULL;
	}
	log_unlock();
}
