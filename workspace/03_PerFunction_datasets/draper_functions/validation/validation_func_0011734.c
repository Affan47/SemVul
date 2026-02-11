amdlibCompareWavelengths(amdlibWAVELENGTH *wave1,
                                       amdlibWAVELENGTH *wave2,
                                       amdlibERROR_MSG  errMsg)
{
    int l;

    amdlibLogTrace("amdlibCompareWavelengths()");

    if ((wave1 == NULL) || (wave2 == NULL))
    {
        amdlibSetErrMsg("Invalid input parameter: NULL value");
        return amdlibFALSE;
    }

    if (wave1->nbWlen != wave2->nbWlen)
    {
        amdlibSetErrMsg("Different number of wavelengths");
        return amdlibFALSE;
    }

    for (l = 0; l < wave1->nbWlen; l++)
    {
        if (wave1->wlen[l] != wave2->wlen[l])
        {
            amdlibSetErrMsg("Different values in wlen array found");
            return amdlibFALSE;
        }
    }

    for (l = 0; l < wave1->nbWlen; l++)
    {
        if (wave1->bandwidth[l] != wave2->bandwidth[l])
        {
            amdlibSetErrMsg("Different in bandwidth array found");
            return amdlibFALSE;
        }
    }

    return amdlibTRUE;
}
