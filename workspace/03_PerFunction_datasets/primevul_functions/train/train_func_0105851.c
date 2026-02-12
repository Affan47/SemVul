char *GfxICCBasedColorSpace::getPostScriptCSA()
{
#    if LCMS_VERSION >= 2070


    if (cmsGetEncodedCMMversion() < 2100)
        return nullptr;

    int size;

    if (psCSA)
        return psCSA;

    if (!profile) {
        error(errSyntaxWarning, -1, "profile is nullptr");
        return nullptr;
    }

    void *rawprofile = profile.get();
    size = cmsGetPostScriptCSA(cmsGetProfileContextID(rawprofile), rawprofile, getIntent(), 0, nullptr, 0);
    if (size == 0) {
        error(errSyntaxWarning, -1, "PostScript CSA is nullptr");
        return nullptr;
    }

    psCSA = (char *)gmalloc(size + 1);
    cmsGetPostScriptCSA(cmsGetProfileContextID(rawprofile), rawprofile, getIntent(), 0, psCSA, size);
    psCSA[size] = 0;


    for (int i = 0; i < size; ++i) {
        if (psCSA[i] == ',')
            psCSA[i] = '.';
    }

    return psCSA;
#    else
    return nullptr;
#    endif
}
