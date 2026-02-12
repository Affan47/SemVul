connection_discard_blank_line (chunkqueue * const cq, uint32_t header_len)
{

    chunkqueue_mark_written(cq, header_len);
    return cq->first;
}
