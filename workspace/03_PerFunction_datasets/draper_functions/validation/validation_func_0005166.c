write_compressed_chunk(struct libjte_env *o,
                                   unsigned char *buffer, size_t size)
{
    int ret;

	if (o->uncomp_buf == NULL)
	{
		if (o->jte_template_compression == JTE_TEMP_BZIP2)
			o->uncomp_size = 900 * 1024;
		else
			o->uncomp_size = 1024 * 1024;
		o->uncomp_buf = malloc(o->uncomp_size);
		if (o->uncomp_buf == NULL)
		{
                   sprintf(o->message_buffer,
                "failed to allocate %lu bytes for template compression buffer",
                           (unsigned long) o->uncomp_size);
                   libjte_add_msg_entry(o, o->message_buffer, 0);
                   exit_if_enabled(o, 1);
                   return -1;
		}
	}

    if ((o->uncomp_buf_used + size) > o->uncomp_size)
    {
        ret = flush_compressed_chunk(o, o->uncomp_buf, o->uncomp_buf_used);
        if (ret <= 0)
            return ret;
        o->uncomp_buf_used = 0;
    }

    if (!size)
    {
        ret = flush_compressed_chunk(o, o->uncomp_buf, o->uncomp_buf_used);
        if (ret <= 0)
            return ret;
        return 1;
    }

    if (!o->uncomp_buf_used)
        memset(o->uncomp_buf, 0, o->uncomp_size);

    while (size > o->uncomp_size)
    {
        ret = flush_compressed_chunk(o, buffer, o->uncomp_size);
        if (ret <= 0)
            return ret;
        buffer += o->uncomp_size;
        size -= o->uncomp_size;
    }
    memcpy(&(o->uncomp_buf[o->uncomp_buf_used]), buffer, size);
    o->uncomp_buf_used += size;
    return 1;
}
