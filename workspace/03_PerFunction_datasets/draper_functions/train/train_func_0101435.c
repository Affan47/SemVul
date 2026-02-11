amdlibMergeP2vmFromFiles(const int  nbFiles,
                                          const char **p2vmFile,
                                          const char *outputFile)
{

    static amdlibP2VM_MATRIX p2vm1;
    static amdlibP2VM_MATRIX p2vm2;
    static amdlibP2VM_MATRIX p2vmRes;
    amdlibERROR_MSG          errMsg;
    int                      i;

    amdlibLogTrace("amdlibMergeP2vmFromFiles()");

    if (nbFiles < 2)
    {
        amdlibLogError("P2VM merge needs at least 2 input files");
        return amdlibFAILURE;
    }

    if (amdlibLoadP2VM(p2vmFile[0], &p2vmRes, errMsg) != amdlibSUCCESS)
    {
        amdlibLogError("Could not load P2VM file '%s'", p2vmFile[0]);
        amdlibLogErrorDetail(errMsg);
        return amdlibFAILURE;
    }
    for (i = 1; i < nbFiles; i++)
    {
        if (amdlibDuplicateP2VM(&p2vmRes, &p2vm1, errMsg) != amdlibSUCCESS)
        {
            amdlibLogError("Could not duplicate P2VM");
            amdlibLogErrorDetail(errMsg);
            amdlibReleaseP2VM(&p2vm2);
            amdlibReleaseP2VM(&p2vmRes);
            return amdlibFAILURE;
        }
        amdlibReleaseP2VM(&p2vmRes);
        if (amdlibLoadP2VM(p2vmFile[i], &p2vm2, errMsg) != amdlibSUCCESS)
        {
            amdlibLogError("Could not load P2VM file '%s'", p2vmFile[i]);
            amdlibLogErrorDetail(errMsg);
            amdlibReleaseP2VM(&p2vm1);
            amdlibReleaseP2VM(&p2vmRes);
            return amdlibFAILURE;
        }
        if (amdlibMergeP2VM(&p2vm1, &p2vm2, &p2vmRes, errMsg) != amdlibSUCCESS)
        {
            amdlibLogError("Could not merge P2VM");
            amdlibLogErrorDetail(errMsg);
            amdlibReleaseP2VM(&p2vm1);
            amdlibReleaseP2VM(&p2vm2);
            amdlibReleaseP2VM(&p2vmRes);
            return amdlibFAILURE;
        }
    }

    if (amdlibSaveP2VM(outputFile, &p2vmRes, amdlibP2VM_STD_ACC,
                       errMsg) != amdlibSUCCESS)
    {
        amdlibLogError("Could not save P2VM");
        amdlibLogErrorDetail(errMsg);
        amdlibReleaseP2VM(&p2vm1);
        amdlibReleaseP2VM(&p2vm2);
        amdlibReleaseP2VM(&p2vmRes);
        return amdlibFAILURE;
    }

    amdlibReleaseP2VM(&p2vm1);
    amdlibReleaseP2VM(&p2vm2);
    amdlibReleaseP2VM(&p2vmRes);
    return amdlibSUCCESS;
}
