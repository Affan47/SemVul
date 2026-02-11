dns_msg_write_question(dns_msg_handle_t *handle, dns_msg_question_t *qdata)
{
    if (msg_encode_name(handle->mh_pos, REMLEN(handle), qdata->mq_name) < 0)
        return -1;
    if (msg_compress_name(handle->mh_pos, handle) < 0)
        return -1;
    if (msg_skip_name(handle) < 0)
        return -1;

    msg_write16(handle, qdata->mq_type);
    msg_write16(handle, qdata->mq_class);

    handle->mh_qdcount++;

    return 0;
}
