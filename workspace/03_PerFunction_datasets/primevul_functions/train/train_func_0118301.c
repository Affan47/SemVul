int WavInFile::readRIFFBlock()
{
    if (fread(&(header.riff), sizeof(WavRiff), 1, fptr) != 1) return -1;


    _swap32((int &)header.riff.package_len);


    if (memcmp(riffStr, header.riff.riff_char, 4) != 0) return -1;

    if (memcmp(waveStr, header.riff.wave, 4) != 0) return -1;

    return 0;
}
