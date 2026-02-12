yaffscache_versions_insert_chunk(YAFFSFS_INFO *yfs, YaffsCacheChunk *chunk)
{
    YaffsCacheObject *obj;
    TSK_RETVAL_ENUM result;
    YaffsCacheVersion *version;


    result = yaffscache_object_find_or_add(yfs, chunk->ycc_obj_id, &obj);
    if (result != TSK_OK) {
        return TSK_ERR;
    }
    version = obj->yco_latest;


    if (version == NULL) {
        yaffscache_object_add_version(obj, chunk);
    }
    else {

        if (chunk->ycc_seq_number == version->ycv_seq_number) {
            version->ycv_last_chunk = chunk;
            if ((chunk->ycc_chunk_id == 0) && (chunk->ycc_parent_id != YAFFS_OBJECT_UNLINKED)
                &&(chunk->ycc_parent_id != YAFFS_OBJECT_DELETED)) {
                    version->ycv_header_chunk = chunk;
            }
            else if((chunk->ycc_chunk_id == 0) && (version->ycv_header_chunk == NULL)){
                version->ycv_header_chunk = chunk;
            }
        }


        else if(version->ycv_header_chunk == NULL){
            version->ycv_seq_number = chunk->ycc_seq_number;
            version->ycv_last_chunk = chunk;
            if ((chunk->ycc_chunk_id == 0) && (chunk->ycc_parent_id != YAFFS_OBJECT_UNLINKED)
                &&(chunk->ycc_parent_id != YAFFS_OBJECT_DELETED)) {
                    version->ycv_header_chunk = chunk;
            }
            else if((chunk->ycc_chunk_id == 0) && (version->ycv_header_chunk == NULL)){
                version->ycv_header_chunk = chunk;
            }
        }
        else if(chunk->ycc_chunk_id == 0){


            YaffsHeader * newHeader;
            yaffsfs_read_header(yfs, &newHeader, chunk->ycc_offset);
            if((newHeader != NULL) && (newHeader->obj_type == YAFFS_TYPE_DIRECTORY)){

                YaffsHeader * oldHeader;
                yaffsfs_read_header(yfs, &oldHeader, version->ycv_header_chunk->ycc_offset);
                if((oldHeader != NULL) && (oldHeader->obj_type == YAFFS_TYPE_DIRECTORY) &&
                    (0 == strncmp(oldHeader->name, newHeader->name, YAFFS_HEADER_NAME_LENGTH))){
                        version->ycv_seq_number = chunk->ycc_seq_number;
                        version->ycv_last_chunk = chunk;
                        version->ycv_header_chunk = chunk;
                }
                else{


                    yaffscache_object_add_version(obj, chunk);
                }
            }
            else{

                yaffscache_object_add_version(obj, chunk);
            }
        }
        else{

            yaffscache_object_add_version(obj, chunk);
        }
    }

    return TSK_OK;
}
