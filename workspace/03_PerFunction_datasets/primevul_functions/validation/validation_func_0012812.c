static avifBool avifParseItemLocationBox(avifMeta * meta, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version;
    CHECK(avifROStreamReadVersionAndFlags(&s, &version, NULL));
    if (version > 2) {
        return AVIF_FALSE;
    }

    uint8_t offsetSizeAndLengthSize;
    CHECK(avifROStreamRead(&s, &offsetSizeAndLengthSize, 1));
    uint8_t offsetSize = (offsetSizeAndLengthSize >> 4) & 0xf;
    uint8_t lengthSize = (offsetSizeAndLengthSize >> 0) & 0xf;

    uint8_t baseOffsetSizeAndIndexSize;
    CHECK(avifROStreamRead(&s, &baseOffsetSizeAndIndexSize, 1));
    uint8_t baseOffsetSize = (baseOffsetSizeAndIndexSize >> 4) & 0xf;
    uint8_t indexSize = 0;
    if ((version == 1) || (version == 2)) {
        indexSize = baseOffsetSizeAndIndexSize & 0xf;
        if (indexSize != 0) {

            return AVIF_FALSE;
        }
    }

    uint16_t tmp16;
    uint32_t itemCount;
    if (version < 2) {
        CHECK(avifROStreamReadU16(&s, &tmp16));
        itemCount = tmp16;
    } else {
        CHECK(avifROStreamReadU32(&s, &itemCount));
    }
    for (uint32_t i = 0; i < itemCount; ++i) {
        uint32_t itemID;
        uint32_t idatID = 0;
        if (version < 2) {
            CHECK(avifROStreamReadU16(&s, &tmp16));
            itemID = tmp16;
        } else {
            CHECK(avifROStreamReadU32(&s, &itemID));
        }

        if ((version == 1) || (version == 2)) {
            uint8_t ignored;
            uint8_t constructionMethod;
            CHECK(avifROStreamRead(&s, &ignored, 1));
            CHECK(avifROStreamRead(&s, &constructionMethod, 1));
            constructionMethod = constructionMethod & 0xf;
            if ((constructionMethod != 0 ) && (constructionMethod != 1 )) {

                return AVIF_FALSE;
            }
            if (constructionMethod == 1) {
                idatID = meta->idatID;
            }
        }

        uint16_t dataReferenceIndex;
        CHECK(avifROStreamReadU16(&s, &dataReferenceIndex));
        uint64_t baseOffset;
        CHECK(avifROStreamReadUX8(&s, &baseOffset, baseOffsetSize));
        uint16_t extentCount;
        CHECK(avifROStreamReadU16(&s, &extentCount));
        if (extentCount == 1) {


            uint64_t extentOffset;
            CHECK(avifROStreamReadUX8(&s, &extentOffset, offsetSize));
            uint64_t extentLength;
            CHECK(avifROStreamReadUX8(&s, &extentLength, lengthSize));

            avifDecoderItem * item = avifMetaFindItem(meta, itemID);
            if (!item) {
                return AVIF_FALSE;
            }
            item->id = itemID;
            item->offset = (uint32_t)(baseOffset + extentOffset);
            item->size = (uint32_t)extentLength;
            item->idatID = idatID;
        } else {

            return AVIF_FALSE;
        }
    }
    return AVIF_TRUE;
}
