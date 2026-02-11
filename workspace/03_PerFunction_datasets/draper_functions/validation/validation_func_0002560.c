findCamRemoteCommand(const char *keyname)
{
    const char *p;
    int keyindex;

    if (keyname == NULL) return -1;
    for (keyindex = 0; keyindex < RFCAMENTRIES; keyindex++) {
        p = RFCAMKeyCodes[keyindex];
        if (p && strcmp(keyname, p) == 0) return keyindex + 0x54;
    }
    return -1;
}
