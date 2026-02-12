static avifBool avifParseItemInfoEntry(avifMeta * meta, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    CHECK(avifROStreamReadAndEnforceVersion(&s, 2));

    uint16_t itemID;
    CHECK(avifROStreamReadU16(&s, &itemID));
    uint16_t itemProtectionIndex;
    CHECK(avifROStreamReadU16(&s, &itemProtectionIndex));
    uint8_t itemType[4];
    CHECK(avifROStreamRead(&s, itemType, 4));

    avifContentType contentType;
    if (!memcmp(itemType, "mime", 4)) {
        CHECK(avifROStreamReadString(&s, NULL, 0));
        CHECK(avifROStreamReadString(&s, contentType.contentType, CONTENTTYPE_SIZE));
    } else {
        memset(&contentType, 0, sizeof(contentType));
    }

    avifDecoderItem * item = avifMetaFindItem(meta, itemID);
    if (!item) {
        return AVIF_FALSE;
    }

    memcpy(item->type, itemType, sizeof(itemType));
    memcpy(&item->contentType, &contentType, sizeof(contentType));
    return AVIF_TRUE;
}
