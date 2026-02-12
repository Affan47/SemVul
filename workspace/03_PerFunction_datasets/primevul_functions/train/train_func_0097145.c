void xclaimCommand(client *c) {
    streamCG *group = NULL;
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    long long minidle;
    long long retrycount = -1;
    mstime_t deliverytime = -1;
    int force = 0;
    int justid = 0;

    if (o) {
        if (checkType(c,o,OBJ_STREAM)) return;
        group = streamLookupCG(o->ptr,c->argv[2]->ptr);
    }


    if (o == NULL || group == NULL) {
        addReplyErrorFormat(c,"-NOGROUP No such key '%s' or "
                              "consumer group '%s'", (char*)c->argv[1]->ptr,
                              (char*)c->argv[2]->ptr);
        return;
    }

    if (getLongLongFromObjectOrReply(c,c->argv[4],&minidle,
        "Invalid min-idle-time argument for XCLAIM")
        != C_OK) return;
    if (minidle < 0) minidle = 0;


    int j;
    streamID static_ids[STREAMID_STATIC_VECTOR_LEN];
    streamID *ids = static_ids;
    int id_count = c->argc-5;
    if (id_count > STREAMID_STATIC_VECTOR_LEN)
        ids = zmalloc(sizeof(streamID)*id_count);
    for (j = 5; j < c->argc; j++) {
        if (streamParseStrictIDOrReply(NULL,c->argv[j],&ids[j-5],0,NULL) != C_OK) break;
    }
    int last_id_arg = j-1;


    mstime_t now = mstime();
    streamID last_id = {0,0};
    int propagate_last_id = 0;
    for (; j < c->argc; j++) {
        int moreargs = (c->argc-1) - j;
        char *opt = c->argv[j]->ptr;
        if (!strcasecmp(opt,"FORCE")) {
            force = 1;
        } else if (!strcasecmp(opt,"JUSTID")) {
            justid = 1;
        } else if (!strcasecmp(opt,"IDLE") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&deliverytime,
                "Invalid IDLE option argument for XCLAIM")
                != C_OK) goto cleanup;
            deliverytime = now - deliverytime;
        } else if (!strcasecmp(opt,"TIME") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&deliverytime,
                "Invalid TIME option argument for XCLAIM")
                != C_OK) goto cleanup;
        } else if (!strcasecmp(opt,"RETRYCOUNT") && moreargs) {
            j++;
            if (getLongLongFromObjectOrReply(c,c->argv[j],&retrycount,
                "Invalid RETRYCOUNT option argument for XCLAIM")
                != C_OK) goto cleanup;
        } else if (!strcasecmp(opt,"LASTID") && moreargs) {
            j++;
            if (streamParseStrictIDOrReply(c,c->argv[j],&last_id,0,NULL) != C_OK) goto cleanup;
        } else {
            addReplyErrorFormat(c,"Unrecognized XCLAIM option '%s'",opt);
            goto cleanup;
        }
    }

    if (streamCompareID(&last_id,&group->last_id) > 0) {
        group->last_id = last_id;
        propagate_last_id = 1;
    }

    if (deliverytime != -1) {


        if (deliverytime < 0 || deliverytime > now) deliverytime = now;
    } else {


        deliverytime = now;
    }


    streamConsumer *consumer = NULL;
    void *arraylenptr = addReplyDeferredLen(c);
    size_t arraylen = 0;
    sds name = c->argv[3]->ptr;
    for (int j = 5; j <= last_id_arg; j++) {
        streamID id = ids[j-5];
        unsigned char buf[sizeof(streamID)];
        streamEncodeID(buf,&id);


        streamNACK *nack = raxFind(group->pel,buf,sizeof(buf));


        if (!streamEntryExists(o->ptr,&id)) {

            if (nack != raxNotFound) {

                streamPropagateXCLAIM(c,c->argv[1],group,c->argv[2],c->argv[j],nack);
                propagate_last_id = 0;
                server.dirty++;

                raxRemove(group->pel,buf,sizeof(buf),NULL);
                raxRemove(nack->consumer->pel,buf,sizeof(buf),NULL);
                streamFreeNACK(nack);
            }
            continue;
        }


        if (force && nack == raxNotFound) {

            nack = streamCreateNACK(NULL);
            raxInsert(group->pel,buf,sizeof(buf),nack,NULL);
        }

        if (nack != raxNotFound) {


            if (nack->consumer && minidle) {
                mstime_t this_idle = now - nack->delivery_time;
                if (this_idle < minidle) continue;
            }

            if (consumer == NULL &&
                (consumer = streamLookupConsumer(group,name,SLC_DEFAULT)) == NULL)
            {
                consumer = streamCreateConsumer(group,name,c->argv[1],c->db->id,SCC_DEFAULT);
            }
            if (nack->consumer != consumer) {


                if (nack->consumer)
                    raxRemove(nack->consumer->pel,buf,sizeof(buf),NULL);
            }
            nack->delivery_time = deliverytime;


            if (retrycount >= 0) {
                nack->delivery_count = retrycount;
            } else if (!justid) {
                nack->delivery_count++;
            }
            if (nack->consumer != consumer) {

                raxInsert(consumer->pel,buf,sizeof(buf),nack,NULL);
                nack->consumer = consumer;
            }

            if (justid) {
                addReplyStreamID(c,&id);
            } else {
                serverAssert(streamReplyWithRange(c,o->ptr,&id,&id,1,0,NULL,NULL,STREAM_RWR_RAWENTRIES,NULL) == 1);
            }
            arraylen++;


            streamPropagateXCLAIM(c,c->argv[1],group,c->argv[2],c->argv[j],nack);
            propagate_last_id = 0;
            server.dirty++;
        }
    }
    if (propagate_last_id) {
        streamPropagateGroupID(c,c->argv[1],group,c->argv[2]);
        server.dirty++;
    }
    setDeferredArrayLen(c,arraylenptr,arraylen);
    preventCommandPropagation(c);
cleanup:
    if (ids != static_ids) zfree(ids);
}
