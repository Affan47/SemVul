writeMultipageTiff(const char  *dirin,
                   const char  *substr,
                   const char  *fileout)
{
SARRAY  *sa;

    PROCNAME("writeMultipageTiff");

    if (!dirin)
        return ERROR_INT("dirin not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);


    sa = getSortedPathnamesInDirectory(dirin, substr, 0, 0);


    writeMultipageTiffSA(sa, fileout);
    sarrayDestroy(&sa);
    return 0;
}
