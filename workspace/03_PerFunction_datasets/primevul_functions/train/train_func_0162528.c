TDStretch * TDStretch::newInstance()
{
    uint uExtensions;

    uExtensions = detectCPUextensions();


#ifdef SOUNDTOUCH_ALLOW_MMX

    if (uExtensions & SUPPORT_MMX)
    {
        return ::new TDStretchMMX;
    }
    else
#endif


#ifdef SOUNDTOUCH_ALLOW_SSE
    if (uExtensions & SUPPORT_SSE)
    {

        return ::new TDStretchSSE;
    }
    else
#endif

    {

        return ::new TDStretch;
    }
}
