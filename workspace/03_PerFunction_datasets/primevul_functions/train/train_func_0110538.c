cmsToneCurve* _cmsBuildKToneCurve(cmsContext        ContextID,
                                   cmsUInt32Number   nPoints,
                                   cmsUInt32Number   nProfiles,
                                   const cmsUInt32Number Intents[],
                                   const cmsHPROFILE hProfiles[],
                                   const cmsBool     BPC[],
                                   const cmsFloat64Number AdaptationStates[],
                                   cmsUInt32Number   dwFlags)
{
    cmsToneCurve *in, *out, *KTone;


    if (cmsGetColorSpace(hProfiles[0]) != cmsSigCmykData ||
        cmsGetColorSpace(hProfiles[nProfiles-1])!= cmsSigCmykData) return NULL;


    if (cmsGetDeviceClass(hProfiles[nProfiles - 1]) != cmsSigOutputClass) return NULL;


    in  = ComputeKToLstar(ContextID, nPoints, nProfiles - 1, Intents, hProfiles, BPC, AdaptationStates, dwFlags);
    if (in == NULL) return NULL;

    out = ComputeKToLstar(ContextID, nPoints, 1,
                            Intents + (nProfiles - 1),
                            hProfiles + (nProfiles - 1),
                            BPC + (nProfiles - 1),
                            AdaptationStates + (nProfiles - 1),
                            dwFlags);
    if (out == NULL) {
        cmsFreeToneCurve(in);
        return NULL;
    }


    KTone = cmsJoinToneCurve(ContextID, in, out, nPoints);


    cmsFreeToneCurve(in); cmsFreeToneCurve(out);


    if (KTone == NULL) return NULL;


    if (!cmsIsToneCurveMonotonic(KTone)) {
        cmsFreeToneCurve(KTone);
        return NULL;
    }

    return KTone;
}
