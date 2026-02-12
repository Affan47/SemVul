yaffscache_chunk_add(YAFFSFS_INFO *yfs, TSK_OFF_T offset, uint32_t seq_number,
    uint32_t obj_id, uint32_t chunk_id, uint32_t parent_id)
{
    TSK_RETVAL_ENUM result;
    YaffsCacheChunk *prev;
    YaffsCacheChunk *chunk;
    if ((chunk = (YaffsCacheChunk*)tsk_malloc(sizeof(YaffsCacheChunk))) == NULL) {
        return TSK_ERR;
    }

    chunk->ycc_offset = offset;
    chunk->ycc_seq_number = seq_number;
    chunk->ycc_obj_id = obj_id;
    chunk->ycc_chunk_id = chunk_id;
    chunk->ycc_parent_id = parent_id;


    if((obj_id == 1) && (parent_id == 1)){
        chunk->ycc_parent_id = 0;
    }


    result = yaffscache_chunk_find_insertion_point(yfs, obj_id, offset, seq_number, &prev);

    if (result == TSK_ERR) {
        return TSK_ERR;
    }

    if (prev == NULL) {

        chunk->ycc_prev = NULL;
        chunk->ycc_next = yfs->chunkMap->operator[](obj_id).cache_chunks_head;
    }
    else {
        chunk->ycc_prev = prev;
        chunk->ycc_next = prev->ycc_next;
    }

    if (chunk->ycc_next != NULL) {

        chunk->ycc_next->ycc_prev = chunk;
    }
    else {
        yfs->chunkMap->operator[](obj_id).cache_chunks_tail = chunk;
    }

    if (chunk->ycc_prev != NULL) {

        chunk->ycc_prev->ycc_next = chunk;
    }
    else {
        yfs->chunkMap->operator[](obj_id).cache_chunks_head = chunk;
    }

    return TSK_OK;
}
