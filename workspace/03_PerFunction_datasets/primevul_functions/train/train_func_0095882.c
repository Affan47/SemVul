static void put_avc_eos_tag(AVIOContext *pb, unsigned ts)
{
    avio_w8(pb, FLV_TAG_TYPE_VIDEO);
    avio_wb24(pb, 5);
    avio_wb24(pb, ts);
    avio_w8(pb, (ts >> 24) & 0x7F);
    avio_wb24(pb, 0);
    avio_w8(pb, 23);
    avio_w8(pb, 2);
    avio_wb24(pb, 0);
    avio_wb32(pb, 16);
}
