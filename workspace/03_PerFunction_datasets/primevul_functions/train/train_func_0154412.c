bool ZRtp::checkMsgHmac(uint8_t* key) {
    uint8_t hmac[IMPL_MAX_DIGEST_LENGTH];
    uint32_t macLen;
    int32_t len = lengthOfMsgData-(HMAC_SIZE);


    hmacFunctionImpl(key, HASH_IMAGE_SIZE, tempMsgBuffer, len, hmac, &macLen);
    return (memcmp(hmac, tempMsgBuffer+len, (HMAC_SIZE)) == 0 ? true : false);
}
