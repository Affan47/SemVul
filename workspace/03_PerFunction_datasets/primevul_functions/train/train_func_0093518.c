int avi_update_header(avi_t *AVI)
{
	int njunk, ms_per_frame, frate, flag;
	int movi_len, hdrl_start, strl_start;
	u32 j;
	unsigned char AVI_header[HEADERBYTES];
	u32 nhb;
	unsigned int xd_size, xd_size_align2;


	movi_len = AVI_MAX_LEN - HEADERBYTES + 4;


	if(AVI->fps < 0.001) {
		frate=0;
		ms_per_frame=0;
	} else {
		frate = (int) (FRAME_RATE_SCALE*AVI->fps + 0.5);
		ms_per_frame=(int) (1000000/AVI->fps + 0.5);
	}


	nhb = 0;


	OUT4CC ("RIFF");
	OUTLONG(movi_len);
	OUT4CC ("AVI ");


	OUT4CC ("LIST");
	OUTLONG(0);
	hdrl_start = nhb;
	OUT4CC ("hdrl");


#define AVIF_HASINDEX           0x00000010
#define AVIF_MUSTUSEINDEX       0x00000020
#define AVIF_ISINTERLEAVED      0x00000100
#define AVIF_TRUSTCKTYPE        0x00000800
#define AVIF_WASCAPTUREFILE     0x00010000
#define AVIF_COPYRIGHTED        0x00020000

	OUT4CC ("avih");
	OUTLONG(56);
	OUTLONG(ms_per_frame);


	OUTLONG(0);
	OUTLONG(0);

	flag = AVIF_ISINTERLEAVED;

		flag |= AVIF_HASINDEX;
	if (AVI->must_use_index)
		flag |= AVIF_MUSTUSEINDEX;
	OUTLONG(flag);
	OUTLONG(0);
	OUTLONG(0);

	OUTLONG(AVI->anum+1);

	OUTLONG(0);
	OUTLONG(AVI->width);
	OUTLONG(AVI->height);

	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);


	OUT4CC ("LIST");
	OUTLONG(0);
	strl_start = nhb;
	OUT4CC ("strl");


	OUT4CC ("strh");
	OUTLONG(56);
	OUT4CC ("vids");
	OUT4CC (AVI->compressor);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(FRAME_RATE_SCALE);
	OUTLONG(frate);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(-1);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);


	xd_size        = AVI->extradata_size;
	xd_size_align2 = (AVI->extradata_size+1) & ~1;

	OUT4CC ("strf");
	OUTLONG(40 + xd_size_align2);
	OUTLONG(40 + xd_size);
	OUTLONG(AVI->width);
	OUTLONG(AVI->height);
	OUTSHRT(1);
	OUTSHRT(24);
	OUT4CC (AVI->compressor);

	OUTLONG(AVI->width*AVI->height*3);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);
	OUTLONG(0);


	if (xd_size > 0 && AVI->extradata) {
		OUTMEM(AVI->extradata, xd_size);
		if (xd_size != xd_size_align2) {
			OUTCHR(0);
		}
	}


	long2str(AVI_header+strl_start-4,nhb-strl_start);


	for(j=0; j<AVI->anum; ++j) {
		int sampsize = avi_sampsize(AVI, j);

		OUT4CC ("LIST");
		OUTLONG(0);
		strl_start = nhb;
		OUT4CC ("strl");


		OUT4CC ("strh");
		OUTLONG(56);
		OUT4CC ("auds");


		OUTLONG(0);


		OUTLONG(0);
		OUTLONG(0);
		OUTLONG(0);


		OUTLONG(sampsize/4);
		OUTLONG(1000*AVI->track[j].mp3rate/8);
		OUTLONG(0);
		OUTLONG(4*AVI->track[j].audio_bytes/sampsize);
		OUTLONG(0);
		OUTLONG(-1);


		OUTLONG(sampsize/4);

		OUTLONG(0);
		OUTLONG(0);


		OUT4CC ("strf");
		OUTLONG(16);
		OUTSHRT(AVI->track[j].a_fmt);
		OUTSHRT(AVI->track[j].a_chans);
		OUTLONG(AVI->track[j].a_rate);

		OUTLONG(1000*AVI->track[j].mp3rate/8);


		OUTSHRT(sampsize/4);


		OUTSHRT(AVI->track[j].a_bits);


		long2str(AVI_header+strl_start-4,nhb-strl_start);
	}


	long2str(AVI_header+hdrl_start-4,nhb-hdrl_start);


	njunk = HEADERBYTES - nhb - 8 - 12;


	if(njunk<=0)
	{
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[avilib] AVI_close_output_file: # of header bytes too small\n"));
		exit(1);
	}

	OUT4CC ("JUNK");
	OUTLONG(njunk);
	memset(AVI_header+nhb,0,njunk);

	nhb += njunk;


	OUT4CC ("LIST");
	OUTLONG(movi_len);
	OUT4CC ("movi");


	if ( (gf_fseek(AVI->fdes, 0, SEEK_SET) ==(u64)-1) ||
	        avi_write(AVI->fdes,(char *)AVI_header,HEADERBYTES)!=HEADERBYTES ||
	        (gf_fseek(AVI->fdes,AVI->pos,SEEK_SET)==(u64)-1)
	   ) {
		AVI_errno = AVI_ERR_CLOSE;
		return -1;
	}

	return 0;
}
