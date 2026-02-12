cmsPipeline* _cmsCreateGamutCheckPipeline(cmsContext ContextID,
										  cmsHPROFILE hProfiles[],
										  cmsBool  BPC[],
										  cmsUInt32Number Intents[],
										  cmsFloat64Number AdaptationStates[],
										  cmsUInt32Number nGamutPCSposition,
										  cmsHPROFILE hGamut)
{
	cmsHPROFILE hLab;
	cmsPipeline* Gamut;
	cmsStage* CLUT;
	cmsUInt32Number dwFormat;
	GAMUTCHAIN Chain;
	int nChannels, nGridpoints;
	cmsColorSpaceSignature ColorSpace;
	cmsUInt32Number i;
	cmsHPROFILE ProfileList[256];
	cmsBool     BPCList[256];
	cmsFloat64Number AdaptationList[256];
	cmsUInt32Number IntentList[256];

	memset(&Chain, 0, sizeof(GAMUTCHAIN));


	if (nGamutPCSposition <= 0 || nGamutPCSposition > 255) {
		cmsSignalError(ContextID, cmsERROR_RANGE, "Wrong position of PCS. 1..255 expected, %d found.", nGamutPCSposition);
		return NULL;
	}

	hLab = cmsCreateLab4ProfileTHR(ContextID, NULL);
	if (hLab == NULL) return NULL;


	if (cmsIsMatrixShaper(hGamut)) {

		Chain.Thereshold = 1.0;
	}
	else {
		Chain.Thereshold = ERR_THERESHOLD;
	}


	for (i=0; i < nGamutPCSposition; i++) {
		ProfileList[i]    = hProfiles[i];
		BPCList[i]        = BPC[i];
		AdaptationList[i] = AdaptationStates[i];
		IntentList[i]     = Intents[i];
	}


	ProfileList[nGamutPCSposition] = hLab;
	BPCList[nGamutPCSposition] = 0;
	AdaptationList[nGamutPCSposition] = 1.0;
	IntentList[nGamutPCSposition] = INTENT_RELATIVE_COLORIMETRIC;


	ColorSpace  = cmsGetColorSpace(hGamut);

	nChannels   = cmsChannelsOf(ColorSpace);
	nGridpoints = _cmsReasonableGridpointsByColorspace(ColorSpace, cmsFLAGS_HIGHRESPRECALC);
	dwFormat    = (CHANNELS_SH(nChannels)|BYTES_SH(2));


	Chain.hInput = cmsCreateExtendedTransform(ContextID,
		nGamutPCSposition + 1,
		ProfileList,
		BPCList,
		IntentList,
		AdaptationList,
		NULL, 0,
		dwFormat, TYPE_Lab_DBL,
		cmsFLAGS_NOCACHE);


	dwFormat    = (CHANNELS_SH(nChannels)|BYTES_SH(2));
	Chain.hForward = cmsCreateTransformTHR(ContextID,
		hLab, TYPE_Lab_DBL,
		hGamut, dwFormat,
		INTENT_RELATIVE_COLORIMETRIC,
		cmsFLAGS_NOCACHE);


	Chain.hReverse = cmsCreateTransformTHR(ContextID, hGamut, dwFormat,
		hLab, TYPE_Lab_DBL,
		INTENT_RELATIVE_COLORIMETRIC,
		cmsFLAGS_NOCACHE);


	if (Chain.hInput && Chain.hForward && Chain.hReverse) {


		Gamut = cmsPipelineAlloc(ContextID, 3, 1);

		if (Gamut != NULL) {

			CLUT = cmsStageAllocCLut16bit(ContextID, nGridpoints, nChannels, 1, NULL);
			if (!cmsPipelineInsertStage(Gamut, cmsAT_BEGIN, CLUT)) {
				cmsPipelineFree(Gamut);
				Gamut = NULL;
			} else
				cmsStageSampleCLut16bit(CLUT, GamutSampler, (void*) &Chain, 0);
		}
	}
	else
		Gamut = NULL;


	if (Chain.hInput)   cmsDeleteTransform(Chain.hInput);
	if (Chain.hForward) cmsDeleteTransform(Chain.hForward);
	if (Chain.hReverse) cmsDeleteTransform(Chain.hReverse);
	if (hLab) cmsCloseProfile(hLab);


	return Gamut;
}
