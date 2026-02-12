static avifBool avifParseItemReferenceBox(avifMeta * meta, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version;
    CHECK(avifROStreamReadVersionAndFlags(&s, &version, NULL));

    while (avifROStreamHasBytesLeft(&s, 1)) {
        avifBoxHeader irefHeader;
        CHECK(avifROStreamReadBoxHeader(&s, &irefHeader));

        uint32_t fromID = 0;
        if (version == 0) {
            uint16_t tmp;
            CHECK(avifROStreamReadU16(&s, &tmp));
            fromID = tmp;
        } else if (version == 1) {
            CHECK(avifROStreamReadU32(&s, &fromID));
        } else {

            break;
        }

        uint16_t referenceCount = 0;
        CHECK(avifROStreamReadU16(&s, &referenceCount));

        for (uint16_t refIndex = 0; refIndex < referenceCount; ++refIndex) {
            uint32_t toID = 0;
            if (version == 0) {
                uint16_t tmp;
                CHECK(avifROStreamReadU16(&s, &tmp));
                toID = tmp;
            } else if (version == 1) {
                CHECK(avifROStreamReadU32(&s, &toID));
            } else {

                break;
            }


            if (fromID && toID) {
                avifDecoderItem * item = avifMetaFindItem(meta, fromID);
                if (!item) {
                    return AVIF_FALSE;
                }

                if (!memcmp(irefHeader.type, "thmb", 4)) {
                    item->thumbnailForID = toID;
                }
                if (!memcmp(irefHeader.type, "auxl", 4)) {
                    item->auxForID = toID;
                }
                if (!memcmp(irefHeader.type, "cdsc", 4)) {
                    item->descForID = toID;
                }
                if (!memcmp(irefHeader.type, "dimg", 4)) {

                    avifDecoderItem * dimg = avifMetaFindItem(meta, toID);
                    if (!dimg) {
                        return AVIF_FALSE;
                    }

                    dimg->dimgForID = fromID;
                }
            }
        }
    }

    return AVIF_TRUE;
}
