ZRtp::~ZRtp() {
    stopZrtp();
    if (DHss != NULL) {
        delete DHss;
        DHss = NULL;
    }
    if (stateEngine != NULL) {
        delete stateEngine;
        stateEngine = NULL;
    }
    if (dhContext != NULL) {
        delete dhContext;
        dhContext = NULL;
    }
    if (msgShaContext != NULL) {
        closeHashCtx(msgShaContext, NULL);
        msgShaContext = NULL;
    }
    if (auxSecret != NULL) {
        delete auxSecret;
        auxSecret = NULL;
        auxSecretLength = 0;
    }
    if (zidRec != NULL) {
        delete zidRec;
        zidRec = NULL;
    }
    memset(hmacKeyI, 0, MAX_DIGEST_LENGTH);
    memset(hmacKeyR, 0, MAX_DIGEST_LENGTH);

    memset(zrtpKeyI, 0, MAX_DIGEST_LENGTH);
    memset(zrtpKeyR, 0, MAX_DIGEST_LENGTH);


    memset(srtpKeyI, 0, MAX_DIGEST_LENGTH);
    memset(srtpSaltI, 0,  MAX_DIGEST_LENGTH);


    memset(srtpKeyR, 0, MAX_DIGEST_LENGTH);
    memset(srtpSaltR, 0, MAX_DIGEST_LENGTH);

    memset(zrtpSession, 0, MAX_DIGEST_LENGTH);
}
