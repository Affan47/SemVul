static avifBool avifParseImageRotationProperty(avifProperty * prop, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    avifImageRotation * irot = &prop->u.irot;
    CHECK(avifROStreamRead(&s, &irot->angle, 1));
    if ((irot->angle & 0xfc) != 0) {

        return AVIF_FALSE;
    }
    return AVIF_TRUE;
}
