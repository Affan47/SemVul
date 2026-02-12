static apr_status_t modsecurity_request_body_store_memory(modsec_rec *msr,
    const char *data, apr_size_t length, char **error_msg)
{
    *error_msg = NULL;


    if ((msr->msc_reqbody_spilltodisk)
        && (msr->msc_reqbody_length + length > (apr_size_t)msr->txcfg->reqbody_inmemory_limit))
    {
        msc_data_chunk **chunks;
        unsigned int disklen = 0;
        int i;

        msr_log(msr, 4, "Input filter: Request too large to store in memory, switching to disk.");


        msr->msc_reqbody_storage = MSC_REQBODY_DISK;
        if (modsecurity_request_body_start_init(msr, error_msg) < 0) return -1;


        chunks = (msc_data_chunk **)msr->msc_reqbody_chunks->elts;
        for(i = 0; i < msr->msc_reqbody_chunks->nelts; i++) {
            disklen += chunks[i]->length;

            if (modsecurity_request_body_store_disk(msr, chunks[i]->data, chunks[i]->length, error_msg) < 0) {
                return -1;
            }

            free(chunks[i]->data);
            chunks[i]->data = NULL;
        }


        msr->msc_reqbody_chunks = NULL;
        apr_pool_clear(msr->msc_reqbody_mp);

        msr_log(msr, 4, "Input filter: Wrote %u bytes from memory to disk.", disklen);


        return modsecurity_request_body_store_disk(msr, data, length, error_msg);
    }


    {
        unsigned long int bucket_offset, bucket_left;

        bucket_offset = 0;
        bucket_left = length;


        while(bucket_left > 0) {

            if (msr->msc_reqbody_chunk_current == NULL) {
                msr->msc_reqbody_chunk_current = (msc_data_chunk *)
                    apr_pcalloc(msr->msc_reqbody_mp, sizeof(msc_data_chunk));
                if (msr->msc_reqbody_chunk_current == NULL) {
                    *error_msg = apr_psprintf(msr->mp, "Input filter: Failed to allocate %lu bytes "
                        "for request body chunk.", (unsigned long)sizeof(msc_data_chunk));
                    return -1;
                }

                msr->msc_reqbody_chunk_current->data = malloc(CHUNK_CAPACITY);
                if (msr->msc_reqbody_chunk_current->data == NULL) {
                    *error_msg = apr_psprintf(msr->mp, "Input filter: Failed to allocate %d bytes "
                        "for request body chunk data.", CHUNK_CAPACITY);
                    return -1;
                }

                msr->msc_reqbody_chunk_current->length = 0;
                msr->msc_reqbody_chunk_current->is_permanent = 1;

                *(const msc_data_chunk **)apr_array_push(msr->msc_reqbody_chunks)
                    = msr->msc_reqbody_chunk_current;
            }

            if (bucket_left < (CHUNK_CAPACITY - msr->msc_reqbody_chunk_current->length)) {

                memcpy(msr->msc_reqbody_chunk_current->data +
                    msr->msc_reqbody_chunk_current->length, data + bucket_offset, bucket_left);
                msr->msc_reqbody_chunk_current->length += bucket_left;
                bucket_left = 0;
            } else {

                unsigned long int copy_length = CHUNK_CAPACITY -
                    msr->msc_reqbody_chunk_current->length;

                memcpy(msr->msc_reqbody_chunk_current->data +
                    msr->msc_reqbody_chunk_current->length, data + bucket_offset, copy_length);
                bucket_offset += copy_length;
                bucket_left -= copy_length;
                msr->msc_reqbody_chunk_current->length += copy_length;


                msr->msc_reqbody_chunk_current = NULL;
            }
        }

        msr->msc_reqbody_length += length;
    }

    return 1;
}
