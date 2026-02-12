void ZRtp::generateKeysResponder(ZrtpPacketDHPart *dhPart, ZIDRecord *zidRec) {
    const uint8_t* setD[3];
    int32_t rsFound = 0;

    setD[0] = setD[1] = setD[2] = NULL;

    detailInfo.secretsMatchedDH = 0;
    if (memcmp(rs1IDi, dhPart->getRs1Id(), HMAC_SIZE) == 0 || memcmp(rs1IDi, dhPart->getRs2Id(), HMAC_SIZE) == 0)
        detailInfo.secretsMatchedDH |= Rs1;
    if (memcmp(rs2IDi, dhPart->getRs1Id(), HMAC_SIZE) == 0 || memcmp(rs2IDi, dhPart->getRs2Id(), HMAC_SIZE) == 0)
        detailInfo.secretsMatchedDH |= Rs2;


    detailInfo.secretsMatched = 0;
    if (memcmp(rs1IDi, dhPart->getRs1Id(), HMAC_SIZE) == 0) {
        setD[0] = zidRec->getRs1();
        rsFound = 0x1;
        detailInfo.secretsMatched = Rs1;
    }
    else if (memcmp(rs1IDi, dhPart->getRs2Id(), HMAC_SIZE) == 0) {
        setD[0] = zidRec->getRs1();
        rsFound = 0x2;
        detailInfo.secretsMatched = Rs1;
    }
    else if (memcmp(rs2IDi, dhPart->getRs1Id(), HMAC_SIZE) == 0) {
        setD[0] = zidRec->getRs2();
        rsFound |= 0x4;
        detailInfo.secretsMatched = Rs2;
    }
    else if (memcmp(rs2IDi, dhPart->getRs2Id(), HMAC_SIZE) == 0) {
        setD[0] = zidRec->getRs2();
        rsFound |= 0x8;
        detailInfo.secretsMatched = Rs2;
    }


    if (memcmp(pbxSecretIDi, dhPart->getPbxSecretId(), 8) == 0) {
        DEBUGOUT((fprintf(stdout, "%c: Match for PBX secret found\n", ownZid[0])));
        setD[2] = zidRec->getMiTMData();
        detailInfo.secretsMatched |= Pbx;
        detailInfo.secretsMatchedDH |= Pbx;
        peerIsEnrolled = true;
    }

    if (rsFound == 0) {
        if (rs1Valid || rs2Valid) {
            sendInfo(Warning, WarningNoExpectedRSMatch);
            zidRec->resetSasVerified();
        }
        else {
            sendInfo(Warning, WarningNoRSMatch);
        }
    }
    else {
        sendInfo(Info, InfoRSMatchFound);
    }


    unsigned char* data[13];
    unsigned int   length[13];
    uint32_t pos = 0;


    uint32_t counter, sLen[3];


    counter = 1;
    counter = zrtpHtonl(counter);
    data[pos] = (unsigned char*)&counter;
    length[pos++] = sizeof(uint32_t);


    data[pos] = DHss;
    length[pos++] = dhContext->getDhSize();


    data[pos] = (unsigned char*)KDFString;
    length[pos++] = strlen(KDFString);


    data[pos] = peerZid;
    length[pos++] = ZID_SIZE;


    data[pos] = ownZid;
    length[pos++] = ZID_SIZE;


    data[pos] = messageHash;
    length[pos++] = hashLength;


    int secretHashLen = RS_LENGTH;
    secretHashLen = zrtpHtonl(secretHashLen);

    for (int32_t i = 0; i < 3; i++) {
        if (setD[i] != NULL) {
            sLen[i] = secretHashLen;
            data[pos] = (unsigned char*)&sLen[i];
            length[pos++] = sizeof(uint32_t);
            data[pos] = (unsigned char*)setD[i];
            length[pos++] = RS_LENGTH;
        }
        else {
            sLen[i] = 0;
            data[pos] = (unsigned char*)&sLen[i];
            length[pos++] = sizeof(uint32_t);
        }
    }

    data[pos] = NULL;
    hashListFunction(data, length, s0);


    memset(DHss, 0, dhContext->getDhSize());
    delete[] DHss;
    DHss = NULL;

    computeSRTPKeys();
    memset(s0, 0, MAX_DIGEST_LENGTH);
}
