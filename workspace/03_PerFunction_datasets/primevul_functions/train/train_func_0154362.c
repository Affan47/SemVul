AlgorithmEnum* ZRtp::findBestAuthLen(ZrtpPacketHello *hello) {

    int  i;
    int ii;
    int numAlgosOffered;
    AlgorithmEnum* algosOffered[ZrtpConfigure::maxNoOfAlgos+2];

    int numAlgosConf;
    AlgorithmEnum* algosConf[ZrtpConfigure::maxNoOfAlgos+2];

    int num = hello->getNumAuth();
    if (num == 0) {
        return &zrtpAuthLengths.getByName(mandatoryAuthLen_1);
    }


    numAlgosConf = configureAlgos.getNumConfiguredAlgos(AuthLength);
    for (i = 0; i < numAlgosConf; i++) {
        algosConf[i] = &configureAlgos.getAlgoAt(AuthLength, i);
    }


    for (numAlgosOffered = 0, i = 0; i < num; i++) {
        algosOffered[numAlgosOffered] = &zrtpAuthLengths.getByName((const char*)hello->getAuthLen(i));
        if (!algosOffered[numAlgosOffered]->isValid())
            continue;
        numAlgosOffered++;
    }


    for (i = 0; i < numAlgosOffered; i++) {
        for (ii = 0; ii < numAlgosConf; ii++) {
            if (*(int32_t*)(algosOffered[i]->getName()) == *(int32_t*)(algosConf[ii]->getName())) {
                return algosConf[ii];
            }
        }
    }

    return &zrtpAuthLengths.getByName(mandatoryAuthLen_1);
}
