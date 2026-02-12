apr_status_t modsecurity_request_body_retrieve(modsec_rec *msr,
    msc_data_chunk **chunk, long int nbytes, char **error_msg)
{
    msc_data_chunk **chunks;

    *error_msg = NULL;

    if (chunk == NULL) {
        *error_msg = apr_pstrdup(msr->mp, "Internal error, retrieving request body chunk.");
        return -1;
    }
    *chunk = NULL;

    if (msr->msc_reqbody_storage == MSC_REQBODY_MEMORY) {

        if (msr->msc_reqbody_chunk_position >= msr->msc_reqbody_chunks->nelts) {

            return 0;
        }


        *chunk = msr->msc_reqbody_disk_chunk;


        chunks = (msc_data_chunk **)msr->msc_reqbody_chunks->elts;
        msr->msc_reqbody_disk_chunk->data = chunks[msr->msc_reqbody_chunk_position]->data
            + msr->msc_reqbody_chunk_offset;

        if (nbytes < 0) {

            msr->msc_reqbody_disk_chunk->length = chunks[msr->msc_reqbody_chunk_position]->length;
            msr->msc_reqbody_chunk_position++;
            msr->msc_reqbody_chunk_offset = 0;
        } else {


            if (chunks[msr->msc_reqbody_chunk_position]->length -
                msr->msc_reqbody_chunk_offset <= (unsigned int)nbytes)
            {


                msr->msc_reqbody_disk_chunk->length =
                    chunks[msr->msc_reqbody_chunk_position]->length -
                    msr->msc_reqbody_chunk_offset;
                msr->msc_reqbody_chunk_position++;
                msr->msc_reqbody_chunk_offset = 0;
            } else {


                msr->msc_reqbody_disk_chunk->length = nbytes;
                msr->msc_reqbody_chunk_offset += nbytes;
            }
        }


        if (msr->msc_reqbody_chunk_position >= msr->msc_reqbody_chunks->nelts) {
            return 0;
        }


        return 1;
    }

    if (msr->msc_reqbody_storage == MSC_REQBODY_DISK) {
        long int my_nbytes = CHUNK_CAPACITY;
        int i;


        if ((nbytes != -1)&&(my_nbytes > nbytes)) {
            my_nbytes = nbytes;
        }

        i = read(msr->msc_reqbody_fd, msr->msc_reqbody_disk_chunk->data, my_nbytes);
        if (i < 0) {
            *error_msg = apr_psprintf(msr->mp, "Input filter: Error reading from temporary file: %s",
                strerror(errno));
            return -1;
        }

        *chunk = msr->msc_reqbody_disk_chunk;
        msr->msc_reqbody_disk_chunk->length = i;

        if (i == 0) return 0;

        return 1;
    }


    *error_msg = apr_psprintf(msr->mp, "Internal error, invalid msc_reqbody_storage value: %u",
        msr->msc_reqbody_storage);

    return -1;
}
