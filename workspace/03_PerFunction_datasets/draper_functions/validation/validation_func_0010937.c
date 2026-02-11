GetBitrate() const
{
    int bitrate_idx = (header & MPEG_BITRATE_MASK) >> 12;
    int layer_idx = layer + ((layer > 0 && mode == MPEG1) ? -1 : 2);
    return mpeg_bitrates[layer_idx][bitrate_idx] * 1000;
}
