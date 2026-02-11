nbt_parse_compressed(const void* chunk_start, size_t length)
{
    struct buffer decompressed = __decompress(chunk_start, length);

    if(decompressed.data == NULL)
        return NULL;

    nbt_node* ret = nbt_parse(decompressed.data, decompressed.len);

    buffer_free(&decompressed);
    return ret;
}
