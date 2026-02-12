GF_Err GetESD(GF_MovieBox *moov, GF_ISOTrackID trackID, u32 StreamDescIndex, GF_ESD **outESD)
{
	GF_Err e;
	GF_ESD *esd;
	u32 track_num = 0;
	u32 k;
	GF_SampleTableBox *stbl;
	GF_TrackBox *trak, *OCRTrack;
	GF_TrackReferenceTypeBox *dpnd;
	GF_SLConfig *slc;
	GF_MPEGSampleEntryBox *entry;

	if (!moov) return GF_ISOM_INVALID_FILE;

	track_num = gf_isom_get_tracknum_from_id(moov, trackID);
	dpnd = NULL;
	*outESD = NULL;

	trak = gf_isom_get_track(moov, track_num);
	if (!trak) return GF_ISOM_INVALID_FILE;

	e = Media_GetESD(trak->Media, StreamDescIndex, &esd, 0);
	if (e) return e;
	if (!esd) return GF_NON_COMPLIANT_BITSTREAM;

	e = Media_GetSampleDesc(trak->Media, StreamDescIndex, (GF_SampleEntryBox **) &entry, NULL);
	if (e) return e;

	esd->ESID = trackID;


	for (k=0; k<3; k++) {
		u32 ref = GF_ISOM_BOX_TYPE_DPND;
		if (k==1) ref = GF_ISOM_REF_BASE;
		else if (k==2) ref = GF_ISOM_REF_SCAL;

		e = Track_FindRef(trak, ref , &dpnd);
		if (e) return e;
		if (dpnd) {

			if (!k && (dpnd->trackIDCount != 1)) return GF_ISOM_INVALID_MEDIA;

			esd->dependsOnESID = dpnd->trackIDs[0];
			break;
		} else {
			esd->dependsOnESID = 0;
		}
	}

	if (trak->udta) {
		GF_UserDataMap *map;
		u32 i = 0;
		while ((map = (GF_UserDataMap*)gf_list_enum(trak->udta->recordList, &i))) {
			if (map->boxType == GF_ISOM_BOX_TYPE_AUXV) {
				GF_Descriptor *d = gf_odf_desc_new(GF_ODF_AUX_VIDEO_DATA);
				gf_list_add(esd->extensionDescriptors, d);
				break;
			}
		}
	}


	dpnd = NULL;
	OCRTrack = NULL;

	e = Track_FindRef(trak, GF_ISOM_BOX_TYPE_SYNC, &dpnd);
	if (e) return e;
	if (dpnd) {
		if (dpnd->trackIDCount != 1) return GF_ISOM_INVALID_MEDIA;
		esd->OCRESID = dpnd->trackIDs[0];
		OCRTrack = gf_isom_get_track_from_id(trak->moov, dpnd->trackIDs[0]);

		while (OCRTrack) {

			e = Track_FindRef(OCRTrack, GF_ISOM_BOX_TYPE_SYNC, &dpnd);
			if (e || !dpnd || !dpnd->trackIDCount) {
				OCRTrack = NULL;
				goto default_sync;
			}

			if ((dpnd->trackIDs[0]==0) || (dpnd->trackIDs[0]==OCRTrack->Header->trackID))
				break;

			if (esd->ESID == (u16) OCRTrack->Header->trackID) {
				OCRTrack = NULL;
				goto default_sync;
			}

			OCRTrack = gf_isom_get_track_from_id(trak->moov, dpnd->trackIDs[0]);
		}
		if (!OCRTrack) goto default_sync;
	} else {
default_sync:

		if (trak->moov->mov->es_id_default_sync<0) {
			if (esd->OCRESID)
				trak->moov->mov->es_id_default_sync = esd->OCRESID;
			else
				trak->moov->mov->es_id_default_sync = esd->ESID;
		}
		if (trak->moov->mov->es_id_default_sync) esd->OCRESID = (u16) trak->moov->mov->es_id_default_sync;

		if (esd->OCRESID == esd->ESID) esd->OCRESID = 0;
	}


	if (esd->ipiPtr != NULL) {
		dpnd = NULL;
		e = Track_FindRef(trak, GF_ISOM_BOX_TYPE_IPIR, &dpnd);
		if (e) return e;
		if (dpnd) {
			if (esd->ipiPtr->tag != GF_ODF_ISOM_IPI_PTR_TAG) return GF_ISOM_INVALID_FILE;

			esd->ipiPtr->IPI_ES_Id = dpnd->trackIDs[esd->ipiPtr->IPI_ES_Id - 1];

			esd->ipiPtr->tag = GF_ODF_IPI_PTR_TAG;
		} else {
			return GF_ISOM_INVALID_FILE;
		}
	}

	if ((trak->Media->mediaHeader->packedLanguage[0] != 'u')
	        || (trak->Media->mediaHeader->packedLanguage[1] != 'n')
	        || (trak->Media->mediaHeader->packedLanguage[2] != 'd') ) {
		if (!esd->langDesc) esd->langDesc = (GF_Language *) gf_odf_desc_new(GF_ODF_LANG_TAG);

		esd->langDesc->langCode = trak->Media->mediaHeader->packedLanguage[0];
		esd->langDesc->langCode <<= 8;
		esd->langDesc->langCode |= trak->Media->mediaHeader->packedLanguage[1];
		esd->langDesc->langCode <<= 8;
		esd->langDesc->langCode |= trak->Media->mediaHeader->packedLanguage[2];
	}


	{
		u16 rvc_predefined;
		u8 *rvc_cfg_data;
		const char *mime_type;
		u32 rvc_cfg_size;
		e = gf_isom_get_rvc_config(moov->mov, track_num, 1, &rvc_predefined, &rvc_cfg_data, &rvc_cfg_size, &mime_type);
		if (e==GF_OK) {
			if (rvc_predefined) {
				esd->decoderConfig->predefined_rvc_config = rvc_predefined;
			} else {
				esd->decoderConfig->rvc_config = (GF_DefaultDescriptor *) gf_odf_desc_new(GF_ODF_DSI_TAG);
				if (mime_type && !strcmp(mime_type, "application/rvc-config+xml+gz") ) {
#if !defined(GPAC_DISABLE_CORE_TOOLS) && !defined(GPAC_DISABLE_ZLIB)
					gf_gz_decompress_payload(rvc_cfg_data, rvc_cfg_size, &esd->decoderConfig->rvc_config->data, &esd->decoderConfig->rvc_config->dataLength);
					gf_free(rvc_cfg_data);
#endif
				} else {
					esd->decoderConfig->rvc_config->data = rvc_cfg_data;
					esd->decoderConfig->rvc_config->dataLength = rvc_cfg_size;
				}
			}
		}
	}


	if (esd->URLString != NULL) {
		*outESD = esd;
		return GF_OK;
	}


	switch (entry->type) {
	case GF_ISOM_BOX_TYPE_MP4V:
		slc = ((GF_MPEGVisualSampleEntryBox *)entry)->slc;
		break;
	case GF_ISOM_BOX_TYPE_MP4A:
		slc = ((GF_MPEGAudioSampleEntryBox *)entry)->slc;
		break;
	case GF_ISOM_BOX_TYPE_MP4S:
		slc = entry->slc;
		break;
	default:
		slc = NULL;
		break;
	}
	if (slc) {
		gf_odf_desc_del((GF_Descriptor *)esd->slConfig);
		gf_odf_desc_copy((GF_Descriptor *)slc, (GF_Descriptor **)&esd->slConfig);
		*outESD = esd;
		return GF_OK;
	}


	if (!esd->slConfig)
		esd->slConfig = (GF_SLConfig *) gf_odf_desc_new(GF_ODF_SLC_TAG);


	esd->slConfig->timestampLength = 32;
	esd->slConfig->timestampResolution = trak->Media->mediaHeader->timeScale;

	esd->slConfig->OCRLength = 0;
	esd->slConfig->OCRResolution = 0;


	stbl = trak->Media->information->sampleTable;


	if (! stbl->SyncSample) {
		if (
#ifndef GPAC_DISABLE_ISOM_FRAGMENTS
		    moov->mvex &&
#endif
		    esd->decoderConfig && esd->decoderConfig->streamType &&
		    (esd->decoderConfig->streamType==GF_STREAM_VISUAL)
		) {
			esd->slConfig->hasRandomAccessUnitsOnlyFlag = 0;
			esd->slConfig->useRandomAccessPointFlag = 1;
			if (trak->moov->mov->openMode!=GF_ISOM_OPEN_READ) {
				stbl->SyncSample = (GF_SyncSampleBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_STSS);
				if (!stbl->SyncSample) return GF_OUT_OF_MEM;
			}
		} else {
			esd->slConfig->hasRandomAccessUnitsOnlyFlag = 1;
			esd->slConfig->useRandomAccessPointFlag = 0;
		}
	} else {
		esd->slConfig->hasRandomAccessUnitsOnlyFlag = 0;

		esd->slConfig->useRandomAccessPointFlag = stbl->SyncSample->nb_entries ? 1 : 0;
	}

	esd->slConfig->useAccessUnitEndFlag = 1;
	esd->slConfig->useAccessUnitStartFlag = 1;


	esd->slConfig->usePaddingFlag = stbl->PaddingBits ? 1 : 0;


	esd->slConfig->degradationPriorityLength = stbl->DegradationPriority ? 32 : 0;


	esd->slConfig->predefined = 0;


	*outESD = esd;
	return GF_OK;
}
