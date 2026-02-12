yaffs_initialize_spare_format(YAFFSFS_INFO * yfs, TSK_OFF_T maxBlocksToTest){


    unsigned int blocksToTest = 10;
    unsigned int chunksToTest = 10;
    unsigned int minChunksRead = 10;

    unsigned int chunkSize = yfs->page_size + yfs->spare_size;
    unsigned int blockSize = yfs->chunks_per_block * chunkSize;

    TSK_FS_INFO *fs = &(yfs->fs_info);
    unsigned char *spareBuffer;

    unsigned int blockIndex;
    unsigned int chunkIndex;

    unsigned int currentOffset;

    unsigned char * allSpares;
    unsigned int allSparesLength;

    TSK_OFF_T maxBlocks;

    bool skipBlock;
    int goodOffset;
    unsigned int nGoodSpares;
    unsigned int nBlocksTested;

    int okOffsetFound = 0;
    int goodOffsetFound = 0;
    int bestOffset = 0;

    bool allSameByte;

    unsigned int i;

    int thisChunkBase;
    int lastChunkBase;


    if(yfs->spare_size < 16){
        if(tsk_verbose && (! yfs->autoDetect)){
            tsk_fprintf(stderr,
                "yaffs_initialize_spare_format failed - given spare size (%d) is not large enough to contain needed fields\n", yfs->spare_size);
        }
        return TSK_ERR;
    }

    if ((spareBuffer = (unsigned char*) tsk_malloc(yfs->spare_size)) == NULL) {
        return TSK_ERR;
    }

    allSparesLength = yfs->spare_size * blocksToTest * chunksToTest;
    if ((allSpares = (unsigned char*) tsk_malloc(allSparesLength)) == NULL) {
        free(spareBuffer);
        return TSK_ERR;
    }


    yfs->spare_seq_offset = 0;
    yfs->spare_obj_id_offset = 4;
    yfs->spare_chunk_id_offset = 8;
    yfs->spare_nbytes_offset = 12;


    maxBlocks = yfs->fs_info.img_info->size / (yfs->chunks_per_block * chunkSize);


    if ((maxBlocksToTest == 0) || (maxBlocksToTest > maxBlocks)){
        maxBlocksToTest = maxBlocks;
    }

    nGoodSpares = 0;
    nBlocksTested = 0;
    for (TSK_OFF_T blockIndex = 0;blockIndex < maxBlocksToTest;blockIndex++){


        TSK_OFF_T offset = (TSK_OFF_T)blockIndex * blockSize + (chunksToTest - 1) * chunkSize + yfs->page_size;
        ssize_t cnt = tsk_img_read(fs->img_info, offset, (char *) spareBuffer,
            yfs->spare_size);
        if ((cnt < 0) || ((unsigned int)cnt < yfs->spare_size)) {
            break;
        }


        skipBlock = true;
        for (i = 0;i < yfs->spare_size;i++){
            if((spareBuffer[i] != 0xff) && (spareBuffer[i] != 0x00)){
                skipBlock = false;
                break;
            }
        }

        if (skipBlock){
            continue;
        }


        nGoodSpares++;
        for (i = 0;i < yfs->spare_size;i++){
            allSpares[nBlocksTested * yfs->spare_size * chunksToTest + (chunksToTest - 1) * yfs->spare_size + i] = spareBuffer[i];
        }


        for (chunkIndex = 0;chunkIndex < chunksToTest - 1;chunkIndex++){
            offset = blockIndex * blockSize + chunkIndex * chunkSize + yfs->page_size;
            cnt = tsk_img_read(fs->img_info, offset, (char *) spareBuffer,
                yfs->spare_size);
            if ((cnt < 0) || ((unsigned int)cnt < yfs->spare_size)) {

                break;
            }

            nGoodSpares++;
            for(i = 0;i < yfs->spare_size;i++){
                allSpares[nBlocksTested * yfs->spare_size * chunksToTest + chunkIndex * yfs->spare_size + i] = spareBuffer[i];
            }
        }


        nBlocksTested++;


        if (nBlocksTested >= blocksToTest){
            break;
        }
    }


    if (nGoodSpares < minChunksRead){

        if (tsk_verbose && (! yfs->autoDetect)){
            tsk_fprintf(stderr,
                "yaffs_initialize_spare_format failed - not enough potentially valid data could be read\n");
        }

        free(spareBuffer);
        free(allSpares);
        return TSK_ERR;
    }

    if (tsk_verbose && (! yfs->autoDetect)){
        tsk_fprintf(stderr,
            "yaffs_initialize_spare_format: Testing potential offsets for the sequence number in the spare area\n");
    }


    if(tsk_verbose && (! yfs->autoDetect)){
        for(blockIndex = 0;blockIndex < nBlocksTested;blockIndex++){
            for(chunkIndex = 0;chunkIndex < chunksToTest;chunkIndex++){
                for(i = 0;i < yfs->spare_size;i++){
                    fprintf(stderr, "%02x", allSpares[blockIndex * yfs->spare_size * chunksToTest + chunkIndex * yfs->spare_size + i]);
                }
                fprintf(stderr, "\n");
            }
        }
    }


    for(currentOffset = 0;currentOffset <= yfs->spare_size - 16;currentOffset++){
        goodOffset = 1;
        for(blockIndex = 0;blockIndex < nBlocksTested;blockIndex++){
            for(chunkIndex = 1;chunkIndex < chunksToTest;chunkIndex++){

                lastChunkBase = blockIndex * yfs->spare_size * chunksToTest + (chunkIndex - 1) * yfs->spare_size;
                thisChunkBase = lastChunkBase + yfs->spare_size;


                if((0xff == allSpares[thisChunkBase + currentOffset]) &&
                    (0xff == allSpares[thisChunkBase + currentOffset + 1]) &&
                    (0xff == allSpares[thisChunkBase + currentOffset + 2]) &&
                    (0xff == allSpares[thisChunkBase + currentOffset + 3])){
                        if(tsk_verbose && (! yfs->autoDetect)){
                            tsk_fprintf(stderr,
                                "yaffs_initialize_spare_format: Eliminating offset %d - invalid sequence number 0xffffffff\n",
                                currentOffset);
                        }
                        goodOffset = 0;
                        break;
                }


                if((0 == allSpares[thisChunkBase + currentOffset]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 1]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 2]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 3])){
                        if(tsk_verbose && (! yfs->autoDetect)){
                            tsk_fprintf(stderr,
                                "yaffs_initialize_spare_format: Eliminating offset %d - invalid sequence number 0\n",
                                currentOffset);
                        }
                        goodOffset = 0;
                        break;
                }


                if((allSpares[lastChunkBase + currentOffset] != allSpares[thisChunkBase + currentOffset]) ||
                    (allSpares[lastChunkBase + currentOffset + 1] != allSpares[thisChunkBase + currentOffset + 1]) ||
                    (allSpares[lastChunkBase + currentOffset + 2] != allSpares[thisChunkBase + currentOffset + 2]) ||
                    (allSpares[lastChunkBase + currentOffset + 3] != allSpares[thisChunkBase + currentOffset + 3])){
                        if(tsk_verbose && (! yfs->autoDetect)){
                            tsk_fprintf(stderr,
                                "yaffs_initialize_spare_format: Eliminating offset %d - did not match previous chunk sequence number\n",
                                currentOffset);
                        }
                        goodOffset = 0;
                        break;
                }


                if((0 == allSpares[thisChunkBase + currentOffset + 4]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 5]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 6]) &&
                    (0 == allSpares[thisChunkBase + currentOffset + 7])){
                        if(tsk_verbose && (! yfs->autoDetect)){
                            tsk_fprintf(stderr,
                                "yaffs_initialize_spare_format: Eliminating offset %d - invalid object id 0\n",
                                currentOffset);
                        }
                        goodOffset = 0;
                        break;
                }


                allSameByte = true;
                for(i = 1;i < 16;i++){
                    if(allSpares[thisChunkBase + currentOffset] != allSpares[thisChunkBase + currentOffset + i]){
                        allSameByte = false;
                        break;
                    }
                }
                if(allSameByte){
                    if(tsk_verbose && (! yfs->autoDetect)){
                        tsk_fprintf(stderr,
                            "yaffs_initialize_spare_format: Eliminating offset %d - all repeated bytes\n",
                            currentOffset);
                    }
                    goodOffset = 0;
                    break;
                }

            }

            if(!goodOffset){
                break;
            }
        }
        if(goodOffset){


            if((! goodOffsetFound) && (! okOffsetFound)){
                bestOffset = currentOffset;
            }
            okOffsetFound = 1;

            if(tsk_verbose && (! yfs->autoDetect)){
                tsk_fprintf(stderr,
                    "yaffs_initialize_spare_format: Found potential spare offsets:  %d (sequence number), %d (object id), %d (chunk id), %d (n bytes)\n",
                    currentOffset, currentOffset+4, currentOffset+8, currentOffset+12);
            }


            int possibleError = 0;


            int firstByteFF = 1;
            for(blockIndex = 0;blockIndex < nBlocksTested;blockIndex++){
                for(chunkIndex = 1;chunkIndex < chunksToTest;chunkIndex++){
                    if(allSpares[blockIndex * yfs->spare_size * chunksToTest + chunkIndex * yfs->spare_size + currentOffset] != 0xff){
                        firstByteFF = 0;
                    }
                }
            }

            if(firstByteFF){
                if(tsk_verbose && (! yfs->autoDetect)){
                    tsk_fprintf(stderr,
                        "yaffs_initialize_spare_format:  Previous data starts with all 0xff bytes. Looking for better offsets.\n");
                }
                possibleError = 1;
            }

            if(! possibleError){


                if(! goodOffsetFound){

                    goodOffsetFound = 1;
                    bestOffset = currentOffset;


                    if(tsk_verbose && (! yfs->autoDetect)){
                        tsk_fprintf(stderr,
                            "yaffs_initialize_spare_format:  Previous offsets appear good - will use as final offsets\n");
                    }

                }
                else{

                    if(tsk_verbose && (! yfs->autoDetect)){
                        tsk_fprintf(stderr,
                            "yaffs_initialize_spare_format:  Previous offsets appear good but staying with earlier valid ones\n");
                    }
                }
            }
        }
    }

    free(spareBuffer);
    free(allSpares);

    if(okOffsetFound || goodOffsetFound){

        yfs->spare_seq_offset = bestOffset;
        yfs->spare_obj_id_offset = bestOffset + 4;
        yfs->spare_chunk_id_offset = bestOffset + 8;
        yfs->spare_nbytes_offset = bestOffset + 12;

        if(tsk_verbose && (! yfs->autoDetect)){
            tsk_fprintf(stderr,
                "yaffs_initialize_spare_format: Final offsets: %d (sequence number), %d (object id), %d (chunk id), %d (n bytes)\n",
                bestOffset, bestOffset+4, bestOffset+8, bestOffset+12);
            tsk_fprintf(stderr,
                "If these do not seem valid: %s\n", YAFFS_HELP_MESSAGE);
        }
        return TSK_OK;
    }
    else{
        return TSK_ERR;
    }
}
