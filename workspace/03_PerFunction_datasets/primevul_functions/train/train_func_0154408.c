bool ZrtpQueue::srtpSecretsReady(SrtpSecret_t* secrets, EnableSecurity part)
{
    CryptoContext* recvCryptoContext;
    CryptoContext* senderCryptoContext;
    CryptoContextCtrl* recvCryptoContextCtrl;
    CryptoContextCtrl* senderCryptoContextCtrl;

    int cipher;
    int authn;
    int authKeyLen;

    if (secrets->authAlgorithm == Sha1) {
        authn = SrtpAuthenticationSha1Hmac;
        authKeyLen = 20;
    }

    if (secrets->authAlgorithm == Skein) {
        authn = SrtpAuthenticationSkeinHmac;
        authKeyLen = 32;
    }

    if (secrets->symEncAlgorithm == Aes)
        cipher = SrtpEncryptionAESCM;

    if (secrets->symEncAlgorithm == TwoFish)
        cipher = SrtpEncryptionTWOCM;

    if (part == ForSender) {


        if (secrets->role == Initiator) {
            senderCryptoContext = new CryptoContext(
                    0,
                    0,
                    0L,
                    cipher,
                    authn,
                    (unsigned char*)secrets->keyInitiator,
                    secrets->initKeyLen / 8,
                    (unsigned char*)secrets->saltInitiator,
                    secrets->initSaltLen / 8,
                    secrets->initKeyLen / 8,
                    authKeyLen,
                    secrets->initSaltLen / 8,
                    secrets->srtpAuthTagLen / 8);
            senderCryptoContextCtrl = new CryptoContextCtrl(0,
                  cipher,
                  authn,
                  (unsigned char*)secrets->keyInitiator,
                  secrets->initKeyLen / 8,
                  (unsigned char*)secrets->saltInitiator,
                  secrets->initSaltLen / 8,
                  secrets->initKeyLen / 8,
                  authKeyLen,
                  secrets->initSaltLen / 8,
                  secrets->srtpAuthTagLen / 8);
        }
        else {
            senderCryptoContext = new CryptoContext(
                    0,
                    0,
                    0L,
                    cipher,
                    authn,
                    (unsigned char*)secrets->keyResponder,
                    secrets->respKeyLen / 8,
                    (unsigned char*)secrets->saltResponder,
                    secrets->respSaltLen / 8,
                    secrets->respKeyLen / 8,
                    authKeyLen,
                    secrets->respSaltLen / 8,
                    secrets->srtpAuthTagLen / 8);
            senderCryptoContextCtrl = new CryptoContextCtrl(0,
                  cipher,
                  authn,
                  (unsigned char*)secrets->keyResponder,
                  secrets->respKeyLen / 8,
                  (unsigned char*)secrets->saltResponder,
                  secrets->respSaltLen / 8,
                  secrets->respKeyLen / 8,
                  authKeyLen,
                  secrets->respSaltLen / 8,
                  secrets->srtpAuthTagLen / 8);
        }
        if (senderCryptoContext == NULL) {
            return false;
        }


         setOutQueueCryptoContext(senderCryptoContext);
         setOutQueueCryptoContextCtrl(senderCryptoContextCtrl);
    }
    if (part == ForReceiver) {


        if (secrets->role == Initiator) {
            recvCryptoContext = new CryptoContext(
                    0,
                    0,
                    0L,
                    cipher,
                    authn,
                    (unsigned char*)secrets->keyResponder,
                    secrets->respKeyLen / 8,
                    (unsigned char*)secrets->saltResponder,
                    secrets->respSaltLen / 8,
                    secrets->respKeyLen / 8,
                    authKeyLen,
                    secrets->respSaltLen / 8,
                    secrets->srtpAuthTagLen / 8);
            recvCryptoContextCtrl = new CryptoContextCtrl(0,
                  cipher,
                  authn,
                  (unsigned char*)secrets->keyResponder,
                  secrets->respKeyLen / 8,
                  (unsigned char*)secrets->saltResponder,
                  secrets->respSaltLen / 8,
                  secrets->respKeyLen / 8,
                  authKeyLen,
                  secrets->respSaltLen / 8,
                  secrets->srtpAuthTagLen / 8);

        }
        else {
            recvCryptoContext = new CryptoContext(
                    0,
                    0,
                    0L,
                    cipher,
                    authn,
                    (unsigned char*)secrets->keyInitiator,
                    secrets->initKeyLen / 8,
                    (unsigned char*)secrets->saltInitiator,
                    secrets->initSaltLen / 8,
                    secrets->initKeyLen / 8,
                    authKeyLen,
                    secrets->initSaltLen / 8,
                    secrets->srtpAuthTagLen / 8);
            recvCryptoContextCtrl = new CryptoContextCtrl(0,
                  cipher,
                  authn,
                  (unsigned char*)secrets->keyInitiator,
                  secrets->initKeyLen / 8,
                  (unsigned char*)secrets->saltInitiator,
                  secrets->initSaltLen / 8,
                  secrets->initKeyLen / 8,
                  authKeyLen,
                  secrets->initSaltLen / 8,
                  secrets->srtpAuthTagLen / 8);
        }
        if (recvCryptoContext == NULL) {
            return false;
        }


        setInQueueCryptoContext(recvCryptoContext);
        setInQueueCryptoContextCtrl(recvCryptoContextCtrl);
    }
    return true;
}
