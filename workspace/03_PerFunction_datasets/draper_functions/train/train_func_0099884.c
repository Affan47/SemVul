boinc_zip(
    int bZipType, const std::string szFileZip, const ZipFileList* pvectszFileIn
) {
    int carg;
    char** av;
    int iRet = 0, i = 0, nVecSize = 0;

    if (pvectszFileIn) nVecSize = pvectszFileIn->size();


    carg = 3 + nVecSize;


    av = (char**) calloc(carg+1, sizeof(char*));
    for (i=0;i<(carg+1);i++) {
        av[i] = (char*) calloc(_MAX_PATH,sizeof(char));
    }


    if (bZipType == ZIP_IT) {
        strcpy(av[0], "zip");

        if (strlen(av[1])==0) {
            strcpy(av[1], "-j9q");
        }
        strcpy(av[2], szFileZip.c_str());


        int jj;
        for (jj=0; jj<nVecSize; jj++) {
            strcpy(av[3+jj], pvectszFileIn->at(jj).c_str());
        }
    } else {
        strcpy(av[0], "unzip");

        if (strlen(av[1])==0) {
            strcpy(av[1], "-oq");
        }
        strcpy(av[2], szFileZip.c_str());


        if (carg == 4) {
            sprintf(av[3], "-d%s", pvectszFileIn->at(0).c_str());
        }
    }
    av[carg] = NULL;


    if (bZipType == ZIP_IT) {
        if (access(szFileZip.c_str(), 0) == 0) {


            unlink(szFileZip.c_str());
        }
        iRet = zipmain(carg, av);
    } else {

        if (access(szFileZip.c_str(), 0) == 0) {
            iRet = UzpMain(carg, av);
        } else {
            iRet = 2;
        }
    }

    for (i=0;i<carg;i++) {
        free(av[i]);
    }
    free(av);
    return iRet;
}
