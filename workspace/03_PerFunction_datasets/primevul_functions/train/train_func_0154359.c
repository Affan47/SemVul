std::string ZRtp::getMultiStrParams() {


    std::string str("");
    char tmp[MAX_DIGEST_LENGTH + 1 + 1 + 1];

    if (inState(SecureState) && !multiStream) {

        tmp[0] = zrtpHashes.getOrdinal(*hash);
        tmp[1] = zrtpAuthLengths.getOrdinal(*authLength);
        tmp[2] = zrtpSymCiphers.getOrdinal(*cipher);
        memcpy(tmp+3, zrtpSession, hashLength);
        str.assign(tmp, hashLength + 1 + 1 + 1);
    }
    return str;
}
