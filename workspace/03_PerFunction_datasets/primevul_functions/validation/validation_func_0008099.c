yaffsfs_block_getflags(TSK_FS_INFO *fs, TSK_DADDR_T a_addr)
{
    YAFFSFS_INFO *yfs = (YAFFSFS_INFO *)fs;
    TSK_FS_BLOCK_FLAG_ENUM flags = TSK_FS_BLOCK_FLAG_UNUSED;

    TSK_OFF_T offset = (a_addr * (fs->block_pre_size + fs->block_size + fs->block_post_size)) + yfs->page_size;
    YaffsSpare *spare = NULL;
    YaffsHeader *header = NULL;
    if (yaffsfs_read_spare(yfs, &spare, offset) != TSK_OK) {

        return flags;
    }

    if (yaffsfs_is_spare_valid(yfs, spare) == TSK_OK) {


        if (spare->chunk_id == 0) {
            flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_META);
        } else {
            flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_CONT);
        }


        YaffsCacheObject * obj = NULL;
        yaffscache_object_find(yfs, spare->object_id, &obj);


        if(obj != NULL){
            if(! yaffs_is_version_allocated(yfs, spare->object_id)){

                flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNALLOC);
            }
            else if (obj->yco_latest == NULL || obj->yco_latest->ycv_header_chunk == NULL) {
                flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNALLOC);
            }
            else if(spare->chunk_id == 0){
                if(obj->yco_latest->ycv_header_chunk->ycc_offset == offset - yfs->page_size){

                    flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_ALLOC);
                }
                else{

                    flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNALLOC);
                }
            }
            else{

                yaffsfs_read_header(yfs, &header, obj->yco_latest->ycv_header_chunk->ycc_offset);


                if(header->file_size <= ((spare->chunk_id - 1) * (fs->block_size))){
                    flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNALLOC);
                }
                else{


                    YaffsCacheChunk * curr = obj->yco_latest->ycv_last_chunk;
                    while(curr != NULL){


                        if(curr->ycc_offset == offset - yfs->page_size){
                            flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_ALLOC);
                            break;
                        }


                        if(curr->ycc_chunk_id == spare->chunk_id){
                            flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNALLOC);
                            break;
                        }
                        curr = curr->ycc_prev;
                    }
                }
            }
        }

    } else {
        flags = (TSK_FS_BLOCK_FLAG_ENUM)(flags | TSK_FS_BLOCK_FLAG_UNUSED | TSK_FS_BLOCK_FLAG_UNALLOC);
    }

    free(spare);
    free(header);
    return flags;
}
