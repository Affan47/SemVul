static avifBool avifParseCleanApertureBoxProperty(avifProperty * prop, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    avifCleanApertureBox * clap = &prop->u.clap;
    CHECK(avifROStreamReadU32(&s, &clap->widthN));
    CHECK(avifROStreamReadU32(&s, &clap->widthD));
    CHECK(avifROStreamReadU32(&s, &clap->heightN));
    CHECK(avifROStreamReadU32(&s, &clap->heightD));
    CHECK(avifROStreamReadU32(&s, &clap->horizOffN));
    CHECK(avifROStreamReadU32(&s, &clap->horizOffD));
    CHECK(avifROStreamReadU32(&s, &clap->vertOffN));
    CHECK(avifROStreamReadU32(&s, &clap->vertOffD));
    return AVIF_TRUE;
}
