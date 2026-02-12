void ZrtpPacketHello::configureHello(ZrtpConfigure* config) {

    nHash = config->getNumConfiguredAlgos(HashAlgorithm);
    nCipher = config->getNumConfiguredAlgos(CipherAlgorithm);
    nPubkey = config->getNumConfiguredAlgos(PubKeyAlgorithm);
    nSas = config->getNumConfiguredAlgos(SasType);
    nAuth = config->getNumConfiguredAlgos(AuthLength);


    int32_t length = sizeof(HelloPacket_t) + (2 * ZRTP_WORD_SIZE);
    length += nHash * ZRTP_WORD_SIZE;
    length += nCipher * ZRTP_WORD_SIZE;
    length += nPubkey * ZRTP_WORD_SIZE;
    length += nSas * ZRTP_WORD_SIZE;
    length += nAuth * ZRTP_WORD_SIZE;


    oHash = sizeof(Hello_t);
    oCipher = oHash + (nHash * ZRTP_WORD_SIZE);
    oAuth = oCipher + (nCipher * ZRTP_WORD_SIZE);
    oPubkey = oAuth + (nAuth * ZRTP_WORD_SIZE);
    oSas = oPubkey + (nPubkey * ZRTP_WORD_SIZE);
    oHmac = oSas + (nSas * ZRTP_WORD_SIZE);

    void* allocated = &data;
    memset(allocated, 0, sizeof(data));

    zrtpHeader = (zrtpPacketHeader_t *)&((HelloPacket_t *)allocated)->hdr;
    helloHeader = (Hello_t *)&((HelloPacket_t *)allocated)->hello;

    setZrtpId();


    setLength(length / ZRTP_WORD_SIZE);
    setMessageType((uint8_t*)HelloMsg);

    uint32_t lenField = nHash << 16;
    for (int32_t i = 0; i < nHash; i++) {
        AlgorithmEnum& hash = config->getAlgoAt(HashAlgorithm, i);
        setHashType(i, (int8_t*)hash.getName());
    }

    lenField |= nCipher << 12;
    for (int32_t i = 0; i < nCipher; i++) {
        AlgorithmEnum& cipher = config->getAlgoAt(CipherAlgorithm, i);
        setCipherType(i, (int8_t*)cipher.getName());
    }

    lenField |= nAuth << 8;
    for (int32_t i = 0; i < nAuth; i++) {
        AlgorithmEnum& length = config->getAlgoAt(AuthLength, i);
        setAuthLen(i, (int8_t*)length.getName());
    }

    lenField |= nPubkey << 4;
    for (int32_t i = 0; i < nPubkey; i++) {
        AlgorithmEnum& pubKey = config->getAlgoAt(PubKeyAlgorithm, i);
        setPubKeyType(i, (int8_t*)pubKey.getName());
    }

    lenField |= nSas;
    for (int32_t i = 0; i < nSas; i++) {
        AlgorithmEnum& sas = config->getAlgoAt(SasType, i);
        setSasType(i, (int8_t*)sas.getName());
    }
    *((uint32_t*)&helloHeader->flags) = zrtpHtonl(lenField);
}
