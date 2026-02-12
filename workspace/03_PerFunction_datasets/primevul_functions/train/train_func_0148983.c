cmsUInt32Number  GenerateCRD(cmsContext ContextID,
                             cmsHPROFILE hProfile,
                             cmsUInt32Number Intent, cmsUInt32Number dwFlags,
                             cmsIOHANDLER* mem)
{
    cmsUInt32Number dwBytesUsed;

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        EmitHeader(mem, "Color Rendering Dictionary (CRD)", hProfile);
    }


    if (cmsGetDeviceClass(hProfile) == cmsSigNamedColorClass) {

        if (!WriteNamedColorCRD(mem, hProfile, Intent, dwFlags)) {
            return 0;
        }
    }
    else {


        if (!WriteOutputLUT(mem, hProfile, Intent, dwFlags)) {
            return 0;
        }
    }

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        _cmsIOPrintf(mem, "%%%%EndResource\n");
        _cmsIOPrintf(mem, "\n%% CRD End\n");
    }


    dwBytesUsed = mem ->UsedSpace;


    return dwBytesUsed;

    cmsUNUSED_PARAMETER(ContextID);
}
