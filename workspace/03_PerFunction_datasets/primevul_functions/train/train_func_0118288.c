int WavInFile::readWavHeaders()
{
    int res;

    memset(&header, 0, sizeof(header));

    res = readRIFFBlock();
    if (res) return 1;

    do
    {

        res = readHeaderBlock();
        if (res < 0) return 1;
    } while (res == 0);

    return checkCharTags();
}
