static int mov_read_pcmc(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int format_flags;

    if (atom.size < 6) {
        av_log(c->fc, AV_LOG_ERROR, "Empty pcmC box\n");
        return AVERROR_INVALIDDATA;
    }

    avio_r8(pb);
    avio_rb24(pb);
    format_flags = avio_r8(pb);
    if (format_flags == 1)
        set_last_stream_little_endian(c->fc);

    return 0;
}
