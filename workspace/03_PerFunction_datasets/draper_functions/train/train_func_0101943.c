oldPositionIDFromKey(const oldpositionkey * pkey)
{

    unsigned char const *puch = pkey->auch;
    static char szID[L_POSITIONID + 1];
    char *pch = szID;
    static char aszBase64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i;

    for (i = 0; i < 3; i++) {
        *pch++ = aszBase64[puch[0] >> 2];
        *pch++ = aszBase64[((puch[0] & 0x03) << 4) | (puch[1] >> 4)];
        *pch++ = aszBase64[((puch[1] & 0x0F) << 2) | (puch[2] >> 6)];
        *pch++ = aszBase64[puch[2] & 0x3F];

        puch += 3;
    }

    *pch++ = aszBase64[*puch >> 2];
    *pch++ = aszBase64[(*puch & 0x03) << 4];

    *pch = 0;

    return szID;
}
