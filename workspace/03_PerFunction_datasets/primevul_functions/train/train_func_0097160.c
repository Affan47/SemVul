void streamDelConsumer(streamCG *cg, streamConsumer *consumer) {


    raxIterator ri;
    raxStart(&ri,consumer->pel);
    raxSeek(&ri,"^",NULL,0);
    while(raxNext(&ri)) {
        streamNACK *nack = ri.data;
        raxRemove(cg->pel,ri.key,ri.key_len,NULL);
        streamFreeNACK(nack);
    }
    raxStop(&ri);


    raxRemove(cg->consumers,(unsigned char*)consumer->name,
              sdslen(consumer->name),NULL);
    streamFreeConsumer(consumer);
}
