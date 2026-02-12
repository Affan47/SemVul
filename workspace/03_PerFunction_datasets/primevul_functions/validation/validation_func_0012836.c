static avifBool avifParseItemDataBox(avifMeta * meta, const uint8_t * raw, size_t rawLen)
{

    for (uint32_t i = 0; i < meta->idats.count; ++i) {
        if (meta->idats.idat[i].id == meta->idatID) {
            return AVIF_FALSE;
        }
    }

    int index = avifArrayPushIndex(&meta->idats);
    avifDecoderItemData * idat = &meta->idats.idat[index];
    idat->id = meta->idatID;
    idat->data.data = raw;
    idat->data.size = rawLen;
    return AVIF_TRUE;
}
