static avifBool avifParsePrimaryItemBox(avifMeta * meta, const uint8_t * raw, size_t rawLen)
{
    if (meta->primaryItemID > 0) {

        return AVIF_FALSE;
    }

    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version;
    CHECK(avifROStreamReadVersionAndFlags(&s, &version, NULL));

    if (version == 0) {
        uint16_t tmp16;
        CHECK(avifROStreamReadU16(&s, &tmp16));
        meta->primaryItemID = tmp16;
    } else {
        CHECK(avifROStreamReadU32(&s, &meta->primaryItemID));
    }
    return AVIF_TRUE;
}
