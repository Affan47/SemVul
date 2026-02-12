void ZRtp::KDF(uint8_t* key, uint32_t keyLength, uint8_t* label, int32_t labelLength,
               uint8_t* context, int32_t contextLength, int32_t L, uint8_t* output) {

    unsigned char* data[6];
    uint32_t length[6];
    uint32_t pos = 0;
    uint32_t maclen = 0;


    uint32_t counter = 1;
    counter = zrtpHtonl(counter);
    data[pos] = (unsigned char*)&counter;
    length[pos++] = sizeof(uint32_t);


    data[pos] = label;
    length[pos++] = labelLength;


    data[pos] = context;
    length[pos++] = contextLength;


    uint32_t len = zrtpHtonl(L);
    data[pos] = (unsigned char*)&len;
    length[pos++] = sizeof(uint32_t);

    data[pos] = NULL;


    hmacListFunction(key, keyLength, data, length, output, &maclen);
}
