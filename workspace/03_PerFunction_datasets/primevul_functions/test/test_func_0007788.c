string RtmpProtocol::get_C1_key(const uint8_t *ptr){


    int offset = 0;
    for (int i = C1_SCHEMA_SIZE - C1_OFFSET_SIZE; i < C1_SCHEMA_SIZE; ++i) {
        offset += ptr[i];
    }
    offset %= (C1_SCHEMA_SIZE - C1_KEY_SIZE - C1_OFFSET_SIZE);
    string key((char *) ptr + offset, C1_KEY_SIZE);

    return key;
}
