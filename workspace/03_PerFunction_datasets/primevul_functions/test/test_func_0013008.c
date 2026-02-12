static void reds_handle_read_magic_done(void *opaque)
{
    RedLinkInfo *link = (RedLinkInfo *)opaque;
    const SpiceLinkHeader *header = &link->link_header;

    if (header->magic != SPICE_MAGIC) {


        if (red_stream_is_websocket(link->stream, &header->magic, sizeof(header->magic))) {
            reds_handle_new_link(link);
            return;
        }
        reds_send_link_error(link, SPICE_LINK_ERR_INVALID_MAGIC);
        reds_link_free(link);
        return;
    }

    red_stream_async_read(link->stream,
                          ((uint8_t *)&link->link_header) + sizeof(header->magic),
                          sizeof(SpiceLinkHeader) - sizeof(header->magic),
                          reds_handle_read_header_done,
                          link);
}
