client_sock_buff_data(const void *data0, size_t length, void *ctx)
{
    struct uo_client *client = ctx;
    const unsigned char *data = data0;

    if (client->compression_enabled) {
        ssize_t nbytes;
        size_t consumed;

        nbytes = client_decompress(client, data, length);
        if (nbytes <= 0)
            return 0;
        consumed = (size_t)nbytes;

        data = fifo_buffer_read(client->decompressed_buffer, &length);
        if (data == NULL)
            return consumed;

        nbytes = client_packets_from_buffer(client, data, length);
        if (nbytes < 0)
            return 0;

        fifo_buffer_consume(client->decompressed_buffer, (size_t)nbytes);

        return consumed;
    } else {
        ssize_t nbytes = client_packets_from_buffer(client, data, length);
        if (nbytes < 0)
            return 0;

        return nbytes;
    }
}
