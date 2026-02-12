static int avi_close_output_file(avi_t *AVI)
{
	int njunk, hasIndex, ms_per_frame, frate, idxerror, flag;
	u64 movi_len;
	int hdrl_start, strl_start;
	u32 j;
	unsigned char AVI_header[HEADERBYTES];
	int nhb;
	unsigned int xd_size, xd_size_align2;

#ifdef INFO_LIST
	int info_len;
	int id_len, real_id_len;
	int info_start_pos;

#endif


	if (AVI->is_opendml) {
		int cur_std_idx = AVI->video_superindex->nEntriesInUse-1;
		u32 audtr;

#ifdef DEBUG_ODML
		GF_LOG(GF_LOG_DEBUG, GF_LOG_CONTAINER, ("[avilib] ODML dump the rest indices\n"));
#endif
		avi_ixnn_entry (AVI, AVI->video_superindex->stdindex[cur_std_idx],
		                &AVI->video_superindex->aIndex[cur_std_idx]);

		AVI->video_superindex->aIndex[cur_std_idx].dwDuration =
		    AVI->video_superindex->stdindex[cur_std_idx]->nEntriesInUse - 1;

		for (audtr = 0; audtr < AVI->anum; audtr++) {
			if (!AVI->track[audtr].audio_superindex) {

				continue;
			}
			avi_ixnn_entry (AVI, AVI->track[audtr].audio_superindex->stdindex[cur_std_idx],
			                &AVI->track[audtr].audio_superindex->aIndex[cur_std_idx]);
			AVI->track[audtr].audio_superindex->aIndex[cur_std_idx].dwDuration =
			    AVI->track[audtr].audio_superindex->stdindex[cur_std_idx]->nEntriesInUse - 1;
			if (AVI->track[audtr].a_fmt == 0x1) {
				AVI->track[audtr].audio_superindex->aIndex[cur_std_idx].dwDuration *=
				    AVI->track[audtr].a_bits*AVI->track[audtr].a_rate*AVI->track[audtr].a_chans/800;
			}
		}

		AVI->video_superindex->stdindex[ cur_std_idx+1 ]->qwBaseOffset = AVI->pos;


		movi_len = AVI->video_superindex->stdindex[ 1 ]->qwBaseOffset - HEADERBYTES+4 - AVI->n_idx*16 - 8;
	} else {
		movi_len = AVI->pos - HEADERBYTES + 4;
	}


	idxerror = 0;
	hasIndex = 1;
	if (!AVI->is_opendml) {

		int ret = avi_add_chunk(AVI, (unsigned char *)"idx1", (unsigned char *)AVI->idx, AVI->n_idx*16);
		hasIndex = (ret==0);


		if(ret) {
			idxerror = 1;
			AVI_errno = AVI_ERR_WRITE_INDEX;
		}
	}


	if(AVI->fps < 0.001) {
		frate=0;
		ms_per_frame=0;
	} else {
		frate = (int) (FRAME_RATE_SCALE*AVI->fps + 0.5);
		ms_per_frame=(int) (1000000/AVI->fps + 0.5);
	}


	nhb = 0;


	OUT4CC ("RIFF");
	if (AVI->is_opendml) {
		OUTLONG(AVI->video_superindex->stdindex[ 1 ]->qwBaseOffset - 8);
	} else {
		OUTLONG(AVI->pos - 8);
	}

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
	if(hasIndex) flag |= AVIF_HASINDEX;
	if(hasIndex && AVI->must_use_index) flag |= AVIF_MUSTUSEINDEX;
	OUTLONG(flag);
	OUTLONG(AVI->video_frames);
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
	OUTLONG(AVI->video_frames);
	OUTLONG(AVI->max_len);
	OUTLONG(0);
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


	if (AVI->is_opendml) {
		u32 k;

		OUT4CC(AVI->video_superindex->fcc);
		OUTLONG(2+1+1+4+4+3*4 + AVI->video_superindex->nEntriesInUse * (8+4+4));
		OUTSHRT(AVI->video_superindex->wLongsPerEntry);
		OUTCHR(AVI->video_superindex->bIndexSubType);
		OUTCHR(AVI->video_superindex->bIndexType);
		OUTLONG(AVI->video_superindex->nEntriesInUse);
		OUT4CC(AVI->video_superindex->dwChunkId);
		OUTLONG(0);
		OUTLONG(0);
		OUTLONG(0);


		for (k = 0; k < AVI->video_superindex->nEntriesInUse; k++) {
			u32 r = (u32) ((AVI->video_superindex->aIndex[k].qwOffset >> 32) & 0xffffffff);
			u32 s = (u32) ((AVI->video_superindex->aIndex[k].qwOffset) & 0xffffffff);

			OUTLONG(s);
			OUTLONG(r);
			OUTLONG(AVI->video_superindex->aIndex[k].dwSize);
			OUTLONG(AVI->video_superindex->aIndex[k].dwDuration);
		}

	}


	long2str(AVI_header+strl_start-4,nhb-strl_start);


	for(j=0; j<AVI->anum; ++j) {


		{
			unsigned int nBlockAlign = 0;
			unsigned int avgbsec = 0;
			unsigned int scalerate = 0;

			int sampsize = avi_sampsize(AVI, j);
			sampsize = AVI->track[j].a_fmt==0x1?sampsize*4:sampsize;

			nBlockAlign = (AVI->track[j].a_rate<32000)?576:1152;


			if (AVI->track[j].a_fmt==0x1) {
				sampsize = (AVI->track[j].a_chans<2)?sampsize/2:sampsize;
				avgbsec = AVI->track[j].a_rate*sampsize/4;
				scalerate = AVI->track[j].a_rate*sampsize/4;
			} else  {
				avgbsec = 1000*AVI->track[j].mp3rate/8;
				scalerate = 1000*AVI->track[j].mp3rate/8;
			}

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


			if (AVI->track[j].a_fmt == 0x55 && AVI->track[j].a_vbr) {
				OUTLONG(nBlockAlign);
				OUTLONG(AVI->track[j].a_rate);
				OUTLONG(0);
				OUTLONG(AVI->track[j].audio_chunks);
				OUTLONG(0);
				OUTLONG(0);
				OUTLONG(0);
				OUTLONG(0);
				OUTLONG(0);
			} else {
				OUTLONG(sampsize/4);
				OUTLONG(scalerate);
				OUTLONG(0);
				OUTLONG(4*AVI->track[j].audio_bytes/sampsize);
				OUTLONG(0);
				OUTLONG(0xffffffff);
				OUTLONG(sampsize/4);
				OUTLONG(0);
				OUTLONG(0);
			}


			OUT4CC ("strf");

			if (AVI->track[j].a_fmt == 0x55 && AVI->track[j].a_vbr) {

				OUTLONG(30);
				OUTSHRT(AVI->track[j].a_fmt);
				OUTSHRT(AVI->track[j].a_chans);
				OUTLONG(AVI->track[j].a_rate);

				OUTLONG(1000*AVI->track[j].mp3rate/8);
				OUTSHRT(nBlockAlign);
				OUTSHRT(AVI->track[j].a_bits);

				OUTSHRT(12);
				OUTSHRT(1);
				OUTLONG(2);
				OUTSHRT(nBlockAlign);
				OUTSHRT(1);
				OUTSHRT(0);

			} else if (AVI->track[j].a_fmt == 0x55 && !AVI->track[j].a_vbr) {

				OUTLONG(30);
				OUTSHRT(AVI->track[j].a_fmt);
				OUTSHRT(AVI->track[j].a_chans);
				OUTLONG(AVI->track[j].a_rate);

				OUTLONG(1000*AVI->track[j].mp3rate/8);
				OUTSHRT(sampsize/4);
				OUTSHRT(AVI->track[j].a_bits);

				OUTSHRT(12);
				OUTSHRT(1);
				OUTLONG(2);
				OUTSHRT(nBlockAlign);
				OUTSHRT(1);
				OUTSHRT(0);

			} else {

				OUTLONG(18);
				OUTSHRT(AVI->track[j].a_fmt);
				OUTSHRT(AVI->track[j].a_chans);
				OUTLONG(AVI->track[j].a_rate);

				OUTLONG(avgbsec);
				OUTSHRT(sampsize/4);
				OUTSHRT(AVI->track[j].a_bits);
				OUTSHRT(0);

			}
		}
		if (AVI->is_opendml) {
			u32 k;

			if (!AVI->track[j].audio_superindex) {

				continue;
			}

			OUT4CC(AVI->track[j].audio_superindex->fcc);
			OUTLONG(2+1+1+4+4+3*4 + AVI->track[j].audio_superindex->nEntriesInUse * (8+4+4));
			OUTSHRT(AVI->track[j].audio_superindex->wLongsPerEntry);
			OUTCHR(AVI->track[j].audio_superindex->bIndexSubType);
			OUTCHR(AVI->track[j].audio_superindex->bIndexType);
			OUTLONG(AVI->track[j].audio_superindex->nEntriesInUse);
			OUT4CC(AVI->track[j].audio_superindex->dwChunkId);
			OUTLONG(0);
			OUTLONG(0);
			OUTLONG(0);

			for (k = 0; k < AVI->track[j].audio_superindex->nEntriesInUse; k++) {
				u32 r = (u32) ((AVI->track[j].audio_superindex->aIndex[k].qwOffset >> 32) & 0xffffffff);
				u32 s = (u32) ((AVI->track[j].audio_superindex->aIndex[k].qwOffset) & 0xffffffff);


				OUTLONG(s);
				OUTLONG(r);
				OUTLONG(AVI->track[j].audio_superindex->aIndex[k].dwSize);
				OUTLONG(AVI->track[j].audio_superindex->aIndex[k].dwDuration);
			}
		}

		long2str(AVI_header+strl_start-4,nhb-strl_start);
	}

	if (AVI->is_opendml) {
		OUT4CC("LIST");
		OUTLONG(16);
		OUT4CC("odml");
		OUT4CC("dmlh");
		OUTLONG(4);
		OUTLONG(AVI->total_frames);
	}


	long2str(AVI_header+hdrl_start-4,nhb-hdrl_start);


#ifdef INFO_LIST
	OUT4CC ("LIST");

	info_start_pos = nhb;
	info_len = MAX_INFO_STRLEN + 12;
	OUTLONG(info_len);
	OUT4CC ("INFO");

	OUT4CC ("ISFT");

	memset(id_str, 0, MAX_INFO_STRLEN);
	if (gf_sys_is_test_mode()) {
		snprintf(id_str, MAX_INFO_STRLEN, "GPAC/avilib");
	} else {
		snprintf(id_str, MAX_INFO_STRLEN, "GPAC/avilib-%s", gf_gpac_version());
	}
	real_id_len = id_len = (u32) strlen(id_str)+1;
	if (id_len&1) id_len++;

	OUTLONG(real_id_len);

	memset(AVI_header+nhb, 0, id_len);
	memcpy(AVI_header+nhb, id_str, id_len);
	nhb += id_len;

	info_len = 0;


	long2str(AVI_header+info_start_pos, info_len + id_len + 4+4+4);

	nhb += info_len;


#endif


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


	if ( (gf_fseek(AVI->fdes,0,SEEK_SET)==(u64)-1) ||
	        avi_write(AVI->fdes,(char *)AVI_header,HEADERBYTES)!=HEADERBYTES

	   )
	{
		AVI_errno = AVI_ERR_CLOSE;
		return -1;
	}


	if (AVI->is_opendml) {
		u32 k;
		char f[4];
		u32 len;

		for (k=1; k<AVI->video_superindex->nEntriesInUse; k++) {

			gf_fseek(AVI->fdes, AVI->video_superindex->stdindex[k]->qwBaseOffset+4, SEEK_SET);
			len = (u32) (AVI->video_superindex->stdindex[k+1]->qwBaseOffset - AVI->video_superindex->stdindex[k]->qwBaseOffset - 8);
			long2str((unsigned char *)f, len);
			avi_write(AVI->fdes, f, 4);


			gf_fseek(AVI->fdes, 8, SEEK_CUR);
			len -= 12;
			long2str((unsigned char *)f, len);
			avi_write(AVI->fdes, f, 4);
		}
	}


	if(idxerror) return -1;

	return 0;
}
