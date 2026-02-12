AlgorithmEnum* ZRtp::findBestCipher(ZrtpPacketHello *hello, AlgorithmEnum* pk) {

    int i;
    int ii;
    int numAlgosOffered;
    AlgorithmEnum* algosOffered[ZrtpConfigure::maxNoOfAlgos+1];

    int numAlgosConf;
    AlgorithmEnum* algosConf[ZrtpConfigure::maxNoOfAlgos+1];

    int num = hello->getNumCiphers();
    if (num == 0 || (*(int32_t*)(pk->getName()) == *(int32_t*)dh2k)) {
        return &zrtpSymCiphers.getByName(aes1);
    }


    numAlgosConf = configureAlgos.getNumConfiguredAlgos(CipherAlgorithm);
    for (i = 0; i < numAlgosConf; i++) {
        algosConf[i] = &configureAlgos.getAlgoAt(CipherAlgorithm, i);
    }

    for (numAlgosOffered = 0, i = 0; i < num; i++) {
        algosOffered[numAlgosOffered] = &zrtpSymCiphers.getByName((const char*)hello->getCipherType(i));
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

    return &zrtpSymCiphers.getByName(mandatoryCipher);
}
