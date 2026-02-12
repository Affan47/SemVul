int ssh_buffer_reinit(struct ssh_buffer_struct *buffer)
{
    if (buffer == NULL) {
        return -1;
    }

    buffer_verify(buffer);

    if (buffer->secure && buffer->allocated > 0) {
        explicit_bzero(buffer->data, buffer->allocated);
    }
    buffer->used = 0;
    buffer->pos = 0;


    if (buffer->allocated > 65536) {
        int rc;


        rc = realloc_buffer(buffer, 65536 - 1);
        if (rc != 0) {
            return -1;
        }
    }

    buffer_verify(buffer);

    return 0;
}
