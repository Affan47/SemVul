int WriteOutputLUT(cmsIOHANDLER* m, cmsHPROFILE hProfile, cmsUInt32Number Intent, cmsUInt32Number dwFlags)
{
    cmsHPROFILE hLab;
    cmsHTRANSFORM xform;
    cmsUInt32Number i, nChannels;
    cmsUInt32Number OutputFormat;
    _cmsTRANSFORM* v;
    cmsPipeline* DeviceLink;
    cmsHPROFILE Profiles[3];
    cmsCIEXYZ BlackPointAdaptedToD50;
    cmsBool lDoBPC = (cmsBool) (dwFlags & cmsFLAGS_BLACKPOINTCOMPENSATION);
    cmsBool lFixWhite = (cmsBool) !(dwFlags & cmsFLAGS_NOWHITEONWHITEFIXUP);
    cmsUInt32Number InFrm = TYPE_Lab_16;
    cmsUInt32Number RelativeEncodingIntent;
    cmsColorSpaceSignature ColorSpace;


    hLab = cmsCreateLab4ProfileTHR(m ->ContextID, NULL);
    if (hLab == NULL) return 0;

    OutputFormat = cmsFormatterForColorspaceOfProfile(hProfile, 2, FALSE);
    nChannels    = T_CHANNELS(OutputFormat);

    ColorSpace = cmsGetColorSpace(hProfile);


    RelativeEncodingIntent = Intent;
    if (RelativeEncodingIntent == INTENT_ABSOLUTE_COLORIMETRIC)
        RelativeEncodingIntent = INTENT_RELATIVE_COLORIMETRIC;


    Profiles[0] = hLab;
    Profiles[1] = hProfile;

    xform = cmsCreateMultiprofileTransformTHR(m ->ContextID,
                                              Profiles, 2, TYPE_Lab_DBL,
                                              OutputFormat, RelativeEncodingIntent, 0);
    cmsCloseProfile(hLab);

    if (xform == NULL) {

        cmsSignalError(m ->ContextID, cmsERROR_COLORSPACE_CHECK, "Cannot create transform Lab -> Profile in CRD creation");
        return 0;
    }


    v = (_cmsTRANSFORM*) xform;
    DeviceLink = cmsPipelineDup(v ->Lut);
    if (DeviceLink == NULL) return 0;


    dwFlags |= cmsFLAGS_FORCE_CLUT;
    _cmsOptimizePipeline(m->ContextID, &DeviceLink, RelativeEncodingIntent, &InFrm, &OutputFormat, &dwFlags);

    _cmsIOPrintf(m, "<<\n");
    _cmsIOPrintf(m, "/ColorRenderingType 1\n");


    cmsDetectBlackPoint(&BlackPointAdaptedToD50, hProfile, Intent, 0);


    EmitWhiteBlackD50(m, &BlackPointAdaptedToD50);
    EmitPQRStage(m, hProfile, lDoBPC, Intent == INTENT_ABSOLUTE_COLORIMETRIC);
    EmitXYZ2Lab(m);


    if (Intent == INTENT_ABSOLUTE_COLORIMETRIC)
            lFixWhite = FALSE;

    _cmsIOPrintf(m, "/RenderTable ");


    WriteCLUT(m, cmsPipelineGetPtrToFirstStage(DeviceLink), "<", ">\n", "", "", lFixWhite, ColorSpace);

    _cmsIOPrintf(m, " %d {} bind ", nChannels);

    for (i=1; i < nChannels; i++)
            _cmsIOPrintf(m, "dup ");

    _cmsIOPrintf(m, "]\n");


    EmitIntent(m, Intent);

    _cmsIOPrintf(m, ">>\n");

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        _cmsIOPrintf(m, "/Current exch /ColorRendering defineresource pop\n");
    }

    cmsPipelineFree(DeviceLink);
    cmsDeleteTransform(xform);

    return 1;
}
