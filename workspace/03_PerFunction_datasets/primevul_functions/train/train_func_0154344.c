ZrtpPacketConf2Ack* ZRtp::prepareConf2Ack(ZrtpPacketConfirm *confirm2, uint32_t* errMsg) {

    sendInfo(Info, InfoRespConf2Received);

    uint8_t confMac[MAX_DIGEST_LENGTH];
    uint32_t macLen;


    int16_t hmlen = (confirm2->getLength() - 9) * ZRTP_WORD_SIZE;


    hmacFunction(hmacKeyI, hashLength,
                 (unsigned char*)confirm2->getHashH0(),
                 hmlen, confMac, &macLen);

    if (memcmp(confMac, confirm2->getHmac(), HMAC_SIZE) != 0) {
        *errMsg = ConfirmHMACWrong;
        return NULL;
    }

    cipher->getDecrypt()(zrtpKeyI, cipher->getKeylen(), (uint8_t*)confirm2->getIv(), confirm2->getHashH0(), hmlen);

    if (!multiStream) {


        if (!checkMsgHmac(confirm2->getHashH0())) {
            sendInfo(Severe, SevereDH2HMACFailed);
            *errMsg = CriticalSWError;
            return NULL;
        }
        signatureLength = confirm2->getSignatureLength();
        if (signSasSeen && signatureLength > 0) {
            signatureData = confirm2->getSignatureData();
            callback->checkSASSignature(sasHash);

        }


        bool sasFlag = confirm2->isSASFlag();


        if (!sasFlag || paranoidMode) {
            zidRec->resetSasVerified();
        }


        zidRec->setNewRs1((const uint8_t*)newRs1);
        getZidCacheInstance()->saveRecord(zidRec);


        if (enableMitmEnrollment && confirm2->isPBXEnrollment()) {
            computePBXSecret();


            if (!peerIsEnrolled) {
                callback->zrtpAskEnrollment(EnrollmentRequest);
            }
            else {
                callback->zrtpAskEnrollment(EnrollmentReconfirm);
            }
        }
    }
    else {


        uint8_t tmpHash[IMPL_MAX_DIGEST_LENGTH];
        hashFunctionImpl(confirm2->getHashH0(), HASH_IMAGE_SIZE, tmpHash);

        if (!checkMsgHmac(tmpHash)) {
            sendInfo(Severe, SevereCommitHMACFailed);
            *errMsg = CriticalSWError;
            return NULL;
        }
    }
    return &zrtpConf2Ack;
}
