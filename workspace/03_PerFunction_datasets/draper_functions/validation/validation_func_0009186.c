mp4_read_descr_len(ByteIOContext *pb)
{
    int len = 0;
    int count = 4;
    while (count--) {
        int c = get_byte(pb);
        len = (len << 7) | (c & 0x7f);
        if (!(c & 0x80))
            break;
    }
    return len;
}
