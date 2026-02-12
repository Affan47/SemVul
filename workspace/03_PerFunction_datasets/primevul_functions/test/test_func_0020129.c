size_t mobi_get_record_extrasize(const MOBIPdbRecord *record, const uint16_t flags) {
    size_t extra_size = 0;
    MOBIBuffer *buf = mobi_buffer_init_null(record->data, record->size);
    if (buf == NULL) {
        debug_print("%s", "Buffer init in extrasize failed\n");
        return MOBI_NOTSET;
    }

    mobi_buffer_setpos(buf, buf->maxlen - 1);
    for (int bit = 15; bit > 0; bit--) {
        if (flags & (1 << bit)) {

            size_t len = 0;

            const uint32_t size = mobi_buffer_get_varlen_dec(buf, &len);


            mobi_buffer_seek(buf, - (int)(size - len));
            extra_size += size;
        }
    };

    if (flags & 1) {
            const uint8_t b = mobi_buffer_get8(buf);

            extra_size += (b & 0x3) + 1;
    }
    mobi_buffer_free_null(buf);
    return extra_size;
}
