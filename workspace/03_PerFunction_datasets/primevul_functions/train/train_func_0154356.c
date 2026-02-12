void ZRtp::setMultiStrParams(std::string parameters) {

    char tmp[MAX_DIGEST_LENGTH + 1 + 1 + 1];


    int i = parameters.at(0) & 0xff;
    hash = &zrtpHashes.getByOrdinal(i);
    setNegotiatedHash(hash);


    parameters.copy(tmp, hashLength + 1 + 1 + 1, 0);

    i = tmp[1] & 0xff;
    authLength = &zrtpAuthLengths.getByOrdinal(i);
    i = tmp[2] & 0xff;
    cipher = &zrtpSymCiphers.getByOrdinal(i);
    memcpy(zrtpSession, tmp+3, hashLength);


    multiStream = true;
    stateEngine->setMultiStream(true);
}
