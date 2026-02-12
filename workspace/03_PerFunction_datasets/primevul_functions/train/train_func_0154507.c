void ZRtp::sendInfo(GnuZrtpCodes::MessageSeverity severity, int32_t subCode) {


    if (severity == Info && subCode == InfoSecureStateOn) {
        memset(srtpKeyI, 0, cipher->getKeylen());
        memset(srtpSaltI, 0, 112/8);
        memset(srtpKeyR, 0, cipher->getKeylen());
        memset(srtpSaltR, 0, 112/8);
    }
    callback->sendInfo(severity, subCode);
}
