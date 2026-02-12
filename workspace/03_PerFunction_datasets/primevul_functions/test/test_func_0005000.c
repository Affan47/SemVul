static char const *acurite_getChannel(uint8_t byte)
{
    static char const *channel_strs[] = {"C", "E", "B", "A"};

    int channel = (byte & 0xC0) >> 6;
    return channel_strs[channel];
}
