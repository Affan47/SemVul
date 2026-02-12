wav_close (SF_PRIVATE *psf)
{
	if (psf->file.mode == SFM_WRITE || psf->file.mode == SFM_RDWR)
	{	wav_write_tailer (psf) ;

		if (psf->file.mode == SFM_RDWR)
		{	sf_count_t current = psf_ftell (psf) ;


			if (current < psf->filelength)
			{	psf_ftruncate (psf, current) ;
				psf->filelength = current ;
				} ;
			} ;

		psf->write_header (psf, SF_TRUE) ;
		} ;

	return 0 ;
}
