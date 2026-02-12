ZrtpPacketConfirm* ZRtp::prepareConfirm2(ZrtpPacketConfirm* confirm1, uint32_t* errMsg) {

    sendInfo(Info, InfoInitConf1Received);

    uint8_t confMac[MAX_DIGEST_LENGTH];
    uint32_t macLen;


    int16_t hmlen = (confirm1->getLength() - 9) * ZRTP_WORD_SIZE;


    hmacFunction(hmacKeyR, hashLength, (unsigned char*)confirm1->getHashH0(), hmlen, confMac, &macLen);

    if (memcmp(confMac, confirm1->getHmac(), HMAC_SIZE) != 0) {
        *errMsg = ConfirmHMACWrong;
        return NULL;
    }
    cipher->getDecrypt()(zrtpKeyR, cipher->getKeylen(), (uint8_t*)confirm1->getIv(), confirm1->getHashH0(), hmlen);


    if (!checkMsgHmac(confirm1->getHashH0())) {
        sendInfo(Severe, SevereDH1HMACFailed);
        *errMsg = CriticalSWError;
        return NULL;
    }
    signatureLength = confirm1->getSignatureLength();
    if (signSasSeen && signatureLength > 0) {
        signatureData = confirm1->getSignatureData();
        callback->checkSASSignature(sasHash);

    }


    bool sasFlag = confirm1->isSASFlag();


    if (!sasFlag || paranoidMode) {
        zidRec->resetSasVerified();
    }


    sasFlag = zidRec->isSasVerified();


    zidRec->setNewRs1((const uint8_t*)newRs1);


    zrtpConfirm2.setMessageType((uint8_t*)Confirm2Msg);
    zrtpConfirm2.setHashH0(H0);

    if (sasFlag) {
        zrtpConfirm2.setSASFlag();
    }
    zrtpConfirm2.setExpTime(0xFFFFFFFF);
    zrtpConfirm2.setIv(randomIV);


    if (enrollmentMode || (enableMitmEnrollment && confirm1->isPBXEnrollment())) {
        computePBXSecret();


        if (enrollmentMode) {


            if (!peerIsEnrolled) {
                computePBXSecret();
                zidRec->setMiTMData(pbxSecretTmp);
            }

            zrtpConfirm2.setPBXEnrollment();
        }
    }
    getZidCacheInstance()->saveRecord(zidRec);


    hmlen = (zrtpConfirm2.getLength() - 9) * ZRTP_WORD_SIZE;
    cipher->getEncrypt()(zrtpKeyI, cipher->getKeylen(), randomIV, zrtpConfirm2.getHashH0(), hmlen);


    hmacFunction(hmacKeyI, hashLength, (unsigned char*)zrtpConfirm2.getHashH0(), hmlen, confMac, &macLen);

    zrtpConfirm2.setHmac(confMac);


    if (enableMitmEnrollment && confirm1->isPBXEnrollment()) {


        if (!peerIsEnrolled) {
            callback->zrtpAskEnrollment(EnrollmentRequest);
        }
        else {
            callback->zrtpAskEnrollment(EnrollmentReconfirm);
        }
    }
    return &zrtpConfirm2;
}
