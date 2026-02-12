ZRtp::ZRtp(uint8_t *myZid, ZrtpCallback *cb, std::string id, ZrtpConfigure* config, bool mitmm, bool sasSignSupport):
        callback(cb), dhContext(NULL), DHss(NULL), auxSecret(NULL), auxSecretLength(0), rs1Valid(false),
        rs2Valid(false), msgShaContext(NULL), hash(NULL), cipher(NULL), pubKey(NULL), sasType(NULL), authLength(NULL),
        multiStream(false), multiStreamAvailable(false), peerIsEnrolled(false), mitmSeen(false), pbxSecretTmp(NULL),
        enrollmentMode(false), configureAlgos(*config), zidRec(NULL) {

    enableMitmEnrollment = config->isTrustedMitM();
    paranoidMode = config->isParanoidMode();


    hashLengthImpl = SHA256_DIGEST_LENGTH;
    hashFunctionImpl = sha256;
    hashListFunctionImpl = sha256;

    hmacFunctionImpl = hmac_sha256;
    hmacListFunctionImpl = hmac_sha256;

    memcpy(ownZid, myZid, ZID_SIZE);


    randomZRTP(H0, HASH_IMAGE_SIZE);
    sha256(H0, HASH_IMAGE_SIZE, H1);
    sha256(H1, HASH_IMAGE_SIZE, H2);
    sha256(H2, HASH_IMAGE_SIZE, H3);


    zrtpHello_11.configureHello(&configureAlgos);
    zrtpHello_11.setH3(H3);
    zrtpHello_11.setZid(ownZid);
    zrtpHello_11.setVersion((uint8_t*)zrtpVersion_11);


    zrtpHello_12.configureHello(&configureAlgos);
    zrtpHello_12.setH3(H3);
    zrtpHello_12.setZid(ownZid);
    zrtpHello_12.setVersion((uint8_t*)zrtpVersion_12);

    if (mitmm) {
        zrtpHello_11.setMitmMode();
        zrtpHello_12.setMitmMode();
    }
    if (sasSignSupport) {
        zrtpHello_11.setSasSign();
        zrtpHello_12.setSasSign();
    }


    helloPackets[0].packet = &zrtpHello_11;
    helloPackets[0].version = zrtpHello_11.getVersionInt();
    setClientId(id, &helloPackets[0]);

    helloPackets[1].packet = &zrtpHello_12;
    helloPackets[1].version = zrtpHello_12.getVersionInt();
    setClientId(id, &helloPackets[1]);

    currentHelloPacket = helloPackets[SUPPORTED_ZRTP_VERSIONS-1].packet;
    helloPackets[SUPPORTED_ZRTP_VERSIONS].packet = NULL;
    peerHelloVersion[0] = 0;

    stateEngine = new ZrtpStateClass(this);
}
