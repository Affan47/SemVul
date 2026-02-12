static avifBool avifParsePixelAspectRatioBoxProperty(avifProperty * prop, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    avifPixelAspectRatioBox * pasp = &prop->u.pasp;
    CHECK(avifROStreamReadU32(&s, &pasp->hSpacing));
    CHECK(avifROStreamReadU32(&s, &pasp->vSpacing));
    return AVIF_TRUE;
}
