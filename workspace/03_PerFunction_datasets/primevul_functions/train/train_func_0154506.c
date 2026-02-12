AlgorithmEnum* ZRtp::findBestHash(ZrtpPacketHello *hello) {

    int i;
    int ii;
    int numAlgosOffered;
    AlgorithmEnum* algosOffered[ZrtpConfigure::maxNoOfAlgos+1];

    int numAlgosConf;
    AlgorithmEnum* algosConf[ZrtpConfigure::maxNoOfAlgos+1];


    int num = hello->getNumHashes();
    if (num == 0) {
        return &zrtpHashes.getByName(mandatoryHash);
    }


    numAlgosConf = configureAlgos.getNumConfiguredAlgos(HashAlgorithm);
    for (i = 0; i < numAlgosConf; i++) {
        algosConf[i] = &configureAlgos.getAlgoAt(HashAlgorithm, i);
    }


    for (numAlgosOffered = 0, i = 0; i < num; i++) {
        algosOffered[numAlgosOffered] = &zrtpHashes.getByName((const char*)hello->getHashType(i));
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
    return &zrtpHashes.getByName(mandatoryHash);
}
