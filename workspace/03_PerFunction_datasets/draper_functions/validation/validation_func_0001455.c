ff_lzw_encode_flush(LZWEncodeState * s)
{
    if (s->last_code != -1)
        writeCode(s, s->last_code);
    writeCode(s, s->end_code);
    flush_put_bits(&s->pb);
    s->last_code = -1;

    return writtenBytes(s);
}
