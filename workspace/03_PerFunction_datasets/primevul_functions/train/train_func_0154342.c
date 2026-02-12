void ZRtp::computeSRTPKeys() {


    uint8_t KDFcontext[sizeof(peerZid)+sizeof(ownZid)+sizeof(messageHash)];
    int32_t kdfSize = sizeof(peerZid)+sizeof(ownZid)+hashLength;

    int32_t keyLen = cipher->getKeylen() * 8;

    if (myRole == Responder) {
        memcpy(KDFcontext, peerZid, sizeof(peerZid));
        memcpy(KDFcontext+sizeof(peerZid), ownZid, sizeof(ownZid));
    }
    else {
        memcpy(KDFcontext, ownZid, sizeof(ownZid));
        memcpy(KDFcontext+sizeof(ownZid), peerZid, sizeof(peerZid));
    }
    memcpy(KDFcontext+sizeof(ownZid)+sizeof(peerZid), messageHash, hashLength);


    KDF(s0, hashLength, (unsigned char*)iniMasterKey, strlen(iniMasterKey)+1, KDFcontext, kdfSize, keyLen, srtpKeyI);
    KDF(s0, hashLength, (unsigned char*)iniMasterSalt, strlen(iniMasterSalt)+1, KDFcontext, kdfSize, 112, srtpSaltI);


    KDF(s0, hashLength, (unsigned char*)respMasterKey, strlen(respMasterKey)+1, KDFcontext, kdfSize, keyLen, srtpKeyR);
    KDF(s0, hashLength, (unsigned char*)respMasterSalt, strlen(respMasterSalt)+1, KDFcontext, kdfSize, 112, srtpSaltR);


    KDF(s0, hashLength, (unsigned char*)iniHmacKey, strlen(iniHmacKey)+1, KDFcontext, kdfSize, hashLength*8, hmacKeyI);
    KDF(s0, hashLength, (unsigned char*)respHmacKey, strlen(respHmacKey)+1, KDFcontext, kdfSize, hashLength*8, hmacKeyR);


    KDF(s0, hashLength, (unsigned char*)iniZrtpKey, strlen(iniZrtpKey)+1, KDFcontext, kdfSize, keyLen, zrtpKeyI);
    KDF(s0, hashLength, (unsigned char*)respZrtpKey, strlen(respZrtpKey)+1, KDFcontext, kdfSize, keyLen, zrtpKeyR);

    detailInfo.pubKey = detailInfo.sasType = NULL;
    if (!multiStream) {

        KDF(s0, hashLength, (unsigned char*)retainedSec, strlen(retainedSec)+1, KDFcontext, kdfSize, SHA256_DIGEST_LENGTH*8, newRs1);


        KDF(s0, hashLength, (unsigned char*)zrtpSessionKey, strlen(zrtpSessionKey)+1, KDFcontext, kdfSize, hashLength*8, zrtpSession);


        uint8_t sasBytes[4];
        KDF(s0, hashLength, (unsigned char*)sasString, strlen(sasString)+1, KDFcontext, kdfSize, SHA256_DIGEST_LENGTH*8, sasHash);


        sasBytes[0] = sasHash[0];
        sasBytes[1] = sasHash[1];
        sasBytes[2] = sasHash[2] & 0xf0;
        sasBytes[3] = 0;
        if (*(int32_t*)b32 == *(int32_t*)(sasType->getName())) {
            SAS = Base32(sasBytes, 20).getEncoded();
        }
        else {
            SAS.assign(sas256WordsEven[sasBytes[0]]).append(":").append(sas256WordsOdd[sasBytes[1]]);
        }

        if (signSasSeen)
            callback->signSAS(sasHash);

        detailInfo.pubKey = pubKey->getReadable();
        detailInfo.sasType = sasType->getReadable();
    }

    detailInfo.authLength = authLength->getReadable();
    detailInfo.cipher = cipher->getReadable();
    detailInfo.hash = hash->getReadable();

    memset(KDFcontext, 0, sizeof(KDFcontext));
}
