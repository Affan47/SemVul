string RtmpProtocol::get_C1_digest(const uint8_t *ptr,char **digestPos){


    int offset = 0;
    for (int i = 0; i < C1_OFFSET_SIZE; ++i) {
        offset += ptr[i];
    }
    offset %= (C1_SCHEMA_SIZE - C1_DIGEST_SIZE - C1_OFFSET_SIZE);
    *digestPos = (char *) ptr + C1_OFFSET_SIZE + offset;
    string digest(*digestPos, C1_DIGEST_SIZE);

    return digest;
}
