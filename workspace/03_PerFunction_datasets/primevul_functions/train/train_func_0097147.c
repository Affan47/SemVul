void xautoclaimCommand(client *c) {
    streamCG *group = NULL;
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    long long minidle;
    long count = 100;
    streamID startid;
    int startex;
    int justid = 0;


    if (getLongLongFromObjectOrReply(c,c->argv[4],&minidle,"Invalid min-idle-time argument for XAUTOCLAIM") != C_OK)
        return;
    if (minidle < 0) minidle = 0;

    if (streamParseIntervalIDOrReply(c,c->argv[5],&startid,&startex,0) != C_OK)
        return;
    if (startex && streamIncrID(&startid) != C_OK) {
        addReplyError(c,"invalid start ID for the interval");
        return;
    }

    int j = 6;
    while(j < c->argc) {
        int moreargs = (c->argc-1) - j;
        char *opt = c->argv[j]->ptr;
        if (!strcasecmp(opt,"COUNT") && moreargs) {
            if (getRangeLongFromObjectOrReply(c,c->argv[j+1],1,LONG_MAX,&count,"COUNT must be > 0") != C_OK)
                return;
            j++;
        } else if (!strcasecmp(opt,"JUSTID")) {
            justid = 1;
        } else {
            addReplyErrorObject(c,shared.syntaxerr);
            return;
        }
        j++;
    }

    if (o) {
        if (checkType(c,o,OBJ_STREAM))
            return;
        group = streamLookupCG(o->ptr,c->argv[2]->ptr);
    }


    if (o == NULL || group == NULL) {
        addReplyErrorFormat(c,"-NOGROUP No such key '%s' or consumer group '%s'",
                            (char*)c->argv[1]->ptr,
                            (char*)c->argv[2]->ptr);
        return;
    }


    streamConsumer *consumer = NULL;
    long long attempts = count*10;

    addReplyArrayLen(c, 3);
    void *endidptr = addReplyDeferredLen(c);
    void *arraylenptr = addReplyDeferredLen(c);

    unsigned char startkey[sizeof(streamID)];
    streamEncodeID(startkey,&startid);
    raxIterator ri;
    raxStart(&ri,group->pel);
    raxSeek(&ri,">=",startkey,sizeof(startkey));
    size_t arraylen = 0;
    mstime_t now = mstime();
    sds name = c->argv[3]->ptr;
    streamID *deleted_ids = zmalloc(count * sizeof(streamID));
    int deleted_id_num = 0;
    while (attempts-- && count && raxNext(&ri)) {
        streamNACK *nack = ri.data;

        streamID id;
        streamDecodeID(ri.key, &id);


        if (!streamEntryExists(o->ptr,&id)) {

            robj *idstr = createObjectFromStreamID(&id);
            streamPropagateXCLAIM(c,c->argv[1],group,c->argv[2],idstr,nack);
            decrRefCount(idstr);
            server.dirty++;

            raxRemove(group->pel,ri.key,ri.key_len,NULL);
            raxRemove(nack->consumer->pel,ri.key,ri.key_len,NULL);
            streamFreeNACK(nack);

            deleted_ids[deleted_id_num++] = id;
            raxSeek(&ri,">=",ri.key,ri.key_len);
            continue;
        }

        if (minidle) {
            mstime_t this_idle = now - nack->delivery_time;
            if (this_idle < minidle)
                continue;
        }

        if (consumer == NULL &&
            (consumer = streamLookupConsumer(group,name,SLC_DEFAULT)) == NULL)
        {
            consumer = streamCreateConsumer(group,name,c->argv[1],c->db->id,SCC_DEFAULT);
        }
        if (nack->consumer != consumer) {


            if (nack->consumer)
                raxRemove(nack->consumer->pel,ri.key,ri.key_len,NULL);
        }


        nack->delivery_time = now;

        if (!justid)
            nack->delivery_count++;

        if (nack->consumer != consumer) {

            raxInsert(consumer->pel,ri.key,ri.key_len,nack,NULL);
            nack->consumer = consumer;
        }


        if (justid) {
            addReplyStreamID(c,&id);
        } else {
            serverAssert(streamReplyWithRange(c,o->ptr,&id,&id,1,0,NULL,NULL,STREAM_RWR_RAWENTRIES,NULL) == 1);
        }
        arraylen++;
        count--;


        robj *idstr = createObjectFromStreamID(&id);
        streamPropagateXCLAIM(c,c->argv[1],group,c->argv[2],idstr,nack);
        decrRefCount(idstr);
        server.dirty++;
    }


    raxNext(&ri);

    streamID endid;
    if (raxEOF(&ri)) {
        endid.ms = endid.seq = 0;
    } else {
        streamDecodeID(ri.key, &endid);
    }
    raxStop(&ri);

    setDeferredArrayLen(c,arraylenptr,arraylen);
    setDeferredReplyStreamID(c,endidptr,&endid);

    addReplyArrayLen(c, deleted_id_num);
    for (int i = 0; i < deleted_id_num; i++) {
        addReplyStreamID(c, &deleted_ids[i]);
    }
    zfree(deleted_ids);

    preventCommandPropagation(c);
}
