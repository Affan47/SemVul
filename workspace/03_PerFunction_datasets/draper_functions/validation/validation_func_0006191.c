shmcb_subcache_iterate(ap_socache_instance_t *instance,
                                           server_rec *s,
                                           void *userctx,
                                           SHMCBHeader *header,
                                           SHMCBSubcache *subcache,
                                           ap_socache_iterator_t *iterator,
                                           unsigned char **buf,
                                           apr_size_t *buf_len,
                                           apr_pool_t *pool,
                                           apr_time_t now)
{
    unsigned int pos;
    unsigned int loop = 0;
    apr_status_t rv;

    pos = subcache->idx_pos;
    while (loop < subcache->idx_used) {
        SHMCBIndex *idx = SHMCB_INDEX(subcache, pos);


        if (!idx->removed) {

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00854)
                         "iterating idx=%d, data=%d", pos, idx->data_pos);
            if (idx->expires > now) {
                unsigned char *id = *buf;
                unsigned char *dest;
                unsigned int data_offset, dest_len;
                apr_size_t buf_req;


                data_offset = SHMCB_CYCLIC_INCREMENT(idx->data_pos,
                                                     idx->id_len,
                                                     header->subcache_data_size);

                dest_len = idx->data_used - idx->id_len;

                buf_req = APR_ALIGN_DEFAULT(idx->id_len + 1)
                        + APR_ALIGN_DEFAULT(dest_len + 1);

                if (buf_req > *buf_len) {


                     *buf_len = buf_req + APR_ALIGN_DEFAULT(buf_req / 2);
                     *buf = apr_palloc(pool, *buf_len);
                     id = *buf;
                }

                dest = *buf + APR_ALIGN_DEFAULT(idx->id_len + 1);


                shmcb_cyclic_cton_memcpy(header->subcache_data_size, id,
                                         SHMCB_DATA(header, subcache),
                                         idx->data_pos, idx->id_len);
                id[idx->id_len] = '\0';

                shmcb_cyclic_cton_memcpy(header->subcache_data_size, dest,
                                         SHMCB_DATA(header, subcache),
                                         data_offset, dest_len);
                dest[dest_len] = '\0';

                rv = iterator(instance, s, userctx, id, idx->id_len,
                              dest, dest_len, pool);
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(00855)
                             "shmcb entry iterated");
                if (rv != APR_SUCCESS)
                    return rv;
            }
            else {

                idx->removed = 1;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00856)
                             "shmcb_subcache_iterate discarding expired entry");
            }
        }

        loop++;
        pos = SHMCB_CYCLIC_INCREMENT(pos, 1, header->index_num);
    }

    return APR_SUCCESS;
}
