static avifBool avifDecoderDataFindMetadata(avifDecoderData * data, avifMeta * meta, avifImage * image, uint32_t colorId)
{
    avifROData exifData = AVIF_DATA_EMPTY;
    avifROData xmpData = AVIF_DATA_EMPTY;

    for (uint32_t itemIndex = 0; itemIndex < meta->items.count; ++itemIndex) {
        avifDecoderItem * item = &meta->items.item[itemIndex];
        if (!item->size) {
            continue;
        }
        if (item->hasUnsupportedEssentialProperty) {

            continue;
        }

        if ((colorId > 0) && (item->descForID != colorId)) {

            continue;
        }

        if (!memcmp(item->type, "Exif", 4)) {

            const uint8_t * boxPtr = avifDecoderDataCalcItemPtr(data, item);
            BEGIN_STREAM(exifBoxStream, boxPtr, item->size);
            uint32_t exifTiffHeaderOffset;
            CHECK(avifROStreamReadU32(&exifBoxStream, &exifTiffHeaderOffset));

            exifData.data = avifROStreamCurrent(&exifBoxStream);
            exifData.size = avifROStreamRemainingBytes(&exifBoxStream);
        } else if (!memcmp(item->type, "mime", 4) && !memcmp(item->contentType.contentType, xmpContentType, xmpContentTypeSize)) {
            xmpData.data = avifDecoderDataCalcItemPtr(data, item);
            xmpData.size = item->size;
        }
    }

    if (exifData.data && exifData.size) {
        avifImageSetMetadataExif(image, exifData.data, exifData.size);
    }
    if (xmpData.data && xmpData.size) {
        avifImageSetMetadataXMP(image, xmpData.data, xmpData.size);
    }
    return AVIF_TRUE;
}
