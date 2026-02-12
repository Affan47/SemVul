cmsFloat64Number CMSEXPORT cmsDetectTAC(cmsHPROFILE hProfile)
{
    cmsTACestimator bp;
    cmsUInt32Number dwFormatter;
    cmsUInt32Number GridPoints[MAX_INPUT_DIMENSIONS];
    cmsHPROFILE hLab;
    cmsContext ContextID = cmsGetProfileContextID(hProfile);


    if (cmsGetDeviceClass(hProfile) != cmsSigOutputClass) {
        return 0;
    }


    dwFormatter = cmsFormatterForColorspaceOfProfile(hProfile, 4, TRUE);

    bp.nOutputChans = T_CHANNELS(dwFormatter);
    bp.MaxTAC = 0;


    if (bp.nOutputChans >= cmsMAXCHANNELS) return 0;

    hLab = cmsCreateLab4ProfileTHR(ContextID, NULL);
    if (hLab == NULL) return 0;

    bp.hRoundTrip = cmsCreateTransformTHR(ContextID, hLab, TYPE_Lab_16,
                                          hProfile, dwFormatter, INTENT_PERCEPTUAL, cmsFLAGS_NOOPTIMIZE|cmsFLAGS_NOCACHE);

    cmsCloseProfile(hLab);
    if (bp.hRoundTrip == NULL) return 0;


    GridPoints[0] = 6;
    GridPoints[1] = 74;
    GridPoints[2] = 74;


	if (!cmsSliceSpace16(3, GridPoints, EstimateTAC, &bp)) {
		bp.MaxTAC = 0;
	}

    cmsDeleteTransform(bp.hRoundTrip);


    return bp.MaxTAC;
}
