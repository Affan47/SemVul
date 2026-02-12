yaffscache_object_add_version(YaffsCacheObject *obj, YaffsCacheChunk *chunk)
{
    uint32_t ver_number;
    YaffsCacheChunk *header_chunk = NULL;
    YaffsCacheVersion *version;


    if ((chunk->ycc_chunk_id == 0) && (chunk->ycc_parent_id != YAFFS_OBJECT_UNLINKED)
        &&(chunk->ycc_parent_id != YAFFS_OBJECT_DELETED)) {
            header_chunk = chunk;
    }


    if (obj->yco_latest != NULL) {
        if (obj->yco_latest->ycv_header_chunk == NULL) {
            YaffsCacheVersion *incomplete = obj->yco_latest;

            if (tsk_verbose)
                tsk_fprintf(stderr, "yaffscache_object_add_version: "
                "removed an incomplete first version (no header)\n");

            obj->yco_latest = obj->yco_latest->ycv_prior;
            free(incomplete);
        }
    }

    if (obj->yco_latest != NULL) {
        ver_number = obj->yco_latest->ycv_version + 1;


        if (header_chunk == NULL) {
            header_chunk = obj->yco_latest->ycv_header_chunk;


            if((header_chunk == NULL) && (chunk->ycc_chunk_id == 0)){
                header_chunk = chunk;
            }
        }
    }
    else {
        ver_number = 1;
    }

    if ((version = (YaffsCacheVersion *) tsk_malloc(sizeof(YaffsCacheVersion))) == NULL) {
        return TSK_ERR;
    }

    version->ycv_prior = obj->yco_latest;
    version->ycv_version = ver_number;
    version->ycv_seq_number = chunk->ycc_seq_number;
    version->ycv_header_chunk = header_chunk;
    version->ycv_first_chunk = chunk;
    version->ycv_last_chunk = chunk;

    obj->yco_latest = version;

    return TSK_OK;
}
