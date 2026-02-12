cmsUInt32Number GenerateCSA(cmsContext ContextID,
                            cmsHPROFILE hProfile,
                            cmsUInt32Number Intent,
                            cmsUInt32Number dwFlags,
                            cmsIOHANDLER* mem)
{
    cmsUInt32Number dwBytesUsed;
    cmsPipeline* lut = NULL;
    cmsStage* Matrix, *Shaper;


    if (cmsGetDeviceClass(hProfile) == cmsSigNamedColorClass) {

        if (!WriteNamedColorCSA(mem, hProfile, Intent)) goto Error;
    }
    else {


        cmsColorSpaceSignature ColorSpace = cmsGetPCS(hProfile);

        if (ColorSpace != cmsSigXYZData &&
            ColorSpace != cmsSigLabData) {

                cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "Invalid output color space");
                goto Error;
        }


        lut = _cmsReadInputLUT(hProfile, Intent);
        if (lut == NULL) goto Error;


        if (cmsPipelineCheckAndRetreiveStages(lut, 2, cmsSigCurveSetElemType, cmsSigMatrixElemType, &Shaper, &Matrix)) {

            if (!WriteInputMatrixShaper(mem, hProfile, Matrix, Shaper)) goto Error;

        }
        else {

           if (!WriteInputLUT(mem, hProfile, Intent, dwFlags)) goto Error;
        }
    }


    dwBytesUsed = mem ->UsedSpace;


    if (lut != NULL) cmsPipelineFree(lut);


    return dwBytesUsed;

Error:
    if (lut != NULL) cmsPipelineFree(lut);
    return 0;
}
