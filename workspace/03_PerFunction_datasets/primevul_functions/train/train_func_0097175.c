void xpendingCommand(client *c) {
    int justinfo = c->argc == 3;

    robj *key = c->argv[1];
    robj *groupname = c->argv[2];
    robj *consumername = NULL;
    streamID startid, endid;
    long long count = 0;
    long long minidle = 0;
    int startex = 0, endex = 0;


    if (c->argc != 3 && (c->argc < 6 || c->argc > 9)) {
        addReplyErrorObject(c,shared.syntaxerr);
        return;
    }


    if (c->argc >= 6) {
        int startidx = 3;

        if (!strcasecmp(c->argv[3]->ptr, "IDLE")) {
            if (getLongLongFromObjectOrReply(c, c->argv[4], &minidle, NULL) == C_ERR)
                return;
            if (c->argc < 8) {

                addReplyErrorObject(c,shared.syntaxerr);
                return;
            }

            startidx += 2;
        }


        if (getLongLongFromObjectOrReply(c,c->argv[startidx+2],&count,NULL) == C_ERR)
            return;
        if (count < 0) count = 0;


        if (streamParseIntervalIDOrReply(c,c->argv[startidx],&startid,&startex,0) != C_OK)
            return;
        if (startex && streamIncrID(&startid) != C_OK) {
            addReplyError(c,"invalid start ID for the interval");
            return;
        }
        if (streamParseIntervalIDOrReply(c,c->argv[startidx+1],&endid,&endex,UINT64_MAX) != C_OK)
            return;
        if (endex && streamDecrID(&endid) != C_OK) {
            addReplyError(c,"invalid end ID for the interval");
            return;
        }

        if (startidx+3 < c->argc) {

            consumername = c->argv[startidx+3];
        }
    }


    robj *o = lookupKeyRead(c->db,c->argv[1]);
    streamCG *group;

    if (checkType(c,o,OBJ_STREAM)) return;
    if (o == NULL ||
        (group = streamLookupCG(o->ptr,groupname->ptr)) == NULL)
    {
        addReplyErrorFormat(c, "-NOGROUP No such key '%s' or consumer "
                               "group '%s'",
                               (char*)key->ptr,(char*)groupname->ptr);
        return;
    }


    if (justinfo) {
        addReplyArrayLen(c,4);

        addReplyLongLong(c,raxSize(group->pel));

        if (raxSize(group->pel) == 0) {
            addReplyNull(c);
            addReplyNull(c);
            addReplyNullArray(c);
        } else {

            raxIterator ri;
            raxStart(&ri,group->pel);
            raxSeek(&ri,"^",NULL,0);
            raxNext(&ri);
            streamDecodeID(ri.key,&startid);
            addReplyStreamID(c,&startid);


            raxSeek(&ri,"$",NULL,0);
            raxNext(&ri);
            streamDecodeID(ri.key,&endid);
            addReplyStreamID(c,&endid);
            raxStop(&ri);


            raxStart(&ri,group->consumers);
            raxSeek(&ri,"^",NULL,0);
            void *arraylen_ptr = addReplyDeferredLen(c);
            size_t arraylen = 0;
            while(raxNext(&ri)) {
                streamConsumer *consumer = ri.data;
                if (raxSize(consumer->pel) == 0) continue;
                addReplyArrayLen(c,2);
                addReplyBulkCBuffer(c,ri.key,ri.key_len);
                addReplyBulkLongLong(c,raxSize(consumer->pel));
                arraylen++;
            }
            setDeferredArrayLen(c,arraylen_ptr,arraylen);
            raxStop(&ri);
        }
    } else {
        streamConsumer *consumer = NULL;
        if (consumername) {
            consumer = streamLookupConsumer(group,consumername->ptr,SLC_NO_REFRESH);


            if (consumer == NULL) {
                addReplyArrayLen(c,0);
                return;
            }
        }

        rax *pel = consumer ? consumer->pel : group->pel;
        unsigned char startkey[sizeof(streamID)];
        unsigned char endkey[sizeof(streamID)];
        raxIterator ri;
        mstime_t now = mstime();

        streamEncodeID(startkey,&startid);
        streamEncodeID(endkey,&endid);
        raxStart(&ri,pel);
        raxSeek(&ri,">=",startkey,sizeof(startkey));
        void *arraylen_ptr = addReplyDeferredLen(c);
        size_t arraylen = 0;

        while(count && raxNext(&ri) && memcmp(ri.key,endkey,ri.key_len) <= 0) {
            streamNACK *nack = ri.data;

            if (minidle) {
                mstime_t this_idle = now - nack->delivery_time;
                if (this_idle < minidle) continue;
            }

            arraylen++;
            count--;
            addReplyArrayLen(c,4);


            streamID id;
            streamDecodeID(ri.key,&id);
            addReplyStreamID(c,&id);


            addReplyBulkCBuffer(c,nack->consumer->name,
                                sdslen(nack->consumer->name));


            mstime_t elapsed = now - nack->delivery_time;
            if (elapsed < 0) elapsed = 0;
            addReplyLongLong(c,elapsed);


            addReplyLongLong(c,nack->delivery_count);
        }
        raxStop(&ri);
        setDeferredArrayLen(c,arraylen_ptr,arraylen);
    }
}
