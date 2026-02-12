void RtmpHandshake::create_complex_c0c1() {
#ifdef ENABLE_OPENSSL
    memcpy(zero, "\x80\x00\x07\x02", 4);

    auto offset_value = rand() % (C1_SCHEMA_SIZE - C1_OFFSET_SIZE - C1_DIGEST_SIZE);

    auto offset_ptr = random + C1_SCHEMA_SIZE;
    offset_ptr[0] = offset_ptr[1] = offset_ptr[2] = offset_value / 4;
    offset_ptr[3] = offset_value - 3 * (offset_value / 4);

    string str((char *) this, sizeof(*this));
    str.erase(8 + C1_SCHEMA_SIZE + C1_OFFSET_SIZE + offset_value, C1_DIGEST_SIZE);

    auto digest_value = openssl_HMACsha256(FPKey, C1_FPKEY_SIZE, str.data(), str.size());

    memcpy(random + C1_SCHEMA_SIZE + C1_OFFSET_SIZE + offset_value, digest_value.data(), digest_value.size());
#endif
}
