archive_compressor_none_init(struct archive_write *a)
{
    int ret;
    struct archive_none *state;

    a->archive.compression_code = ARCHIVE_COMPRESSION_NONE;
    a->archive.compression_name = "none";

    if (a->client_opener != NULL) {
        ret = (a->client_opener)(&a->archive, a->client_data);
        if (ret != 0)
            return (ret);
    }

    state = (struct archive_none *)malloc(sizeof(*state));
    if (state == NULL) {
        archive_set_error(&a->archive, ENOMEM,
            "Can't allocate data for output buffering");
        return (ARCHIVE_FATAL);
    }
    memset(state, 0, sizeof(*state));

    state->buffer_size = a->bytes_per_block;
    if (state->buffer_size != 0) {
        state->buffer = (char *)malloc(state->buffer_size);
        if (state->buffer == NULL) {
            archive_set_error(&a->archive, ENOMEM,
                "Can't allocate output buffer");
            free(state);
            return (ARCHIVE_FATAL);
        }
    }

    state->next = state->buffer;
    state->avail = state->buffer_size;

    a->compressor.data = state;
    a->compressor.write = archive_compressor_none_write;
    a->compressor.finish = archive_compressor_none_finish;
    return (ARCHIVE_OK);
}
