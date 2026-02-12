void xinfoCommand(client *c) {
    stream *s = NULL;
    char *opt;
    robj *key;


    if (!strcasecmp(c->argv[1]->ptr,"HELP")) {
        if (c->argc != 2) {
            addReplySubcommandSyntaxError(c);
            return;
        }

        const char *help[] = {
"CONSUMERS <key> <groupname>",
"    Show consumers of <groupname>.",
"GROUPS <key>",
"    Show the stream consumer groups.",
"STREAM <key> [FULL [COUNT <count>]",
"    Show information about the stream.",
NULL
        };
        addReplyHelp(c, help);
        return;
    } else if (c->argc < 3) {
        addReplySubcommandSyntaxError(c);
        return;
    }


    opt = c->argv[1]->ptr;
    key = c->argv[2];


    robj *o = lookupKeyReadOrReply(c,key,shared.nokeyerr);
    if (o == NULL || checkType(c,o,OBJ_STREAM)) return;
    s = o->ptr;


    if (!strcasecmp(opt,"CONSUMERS") && c->argc == 4) {

        streamCG *cg = streamLookupCG(s,c->argv[3]->ptr);
        if (cg == NULL) {
            addReplyErrorFormat(c, "-NOGROUP No such consumer group '%s' "
                                   "for key name '%s'",
                                   (char*)c->argv[3]->ptr, (char*)key->ptr);
            return;
        }

        addReplyArrayLen(c,raxSize(cg->consumers));
        raxIterator ri;
        raxStart(&ri,cg->consumers);
        raxSeek(&ri,"^",NULL,0);
        mstime_t now = mstime();
        while(raxNext(&ri)) {
            streamConsumer *consumer = ri.data;
            mstime_t idle = now - consumer->seen_time;
            if (idle < 0) idle = 0;

            addReplyMapLen(c,3);
            addReplyBulkCString(c,"name");
            addReplyBulkCBuffer(c,consumer->name,sdslen(consumer->name));
            addReplyBulkCString(c,"pending");
            addReplyLongLong(c,raxSize(consumer->pel));
            addReplyBulkCString(c,"idle");
            addReplyLongLong(c,idle);
        }
        raxStop(&ri);
    } else if (!strcasecmp(opt,"GROUPS") && c->argc == 3) {

        if (s->cgroups == NULL) {
            addReplyArrayLen(c,0);
            return;
        }

        addReplyArrayLen(c,raxSize(s->cgroups));
        raxIterator ri;
        raxStart(&ri,s->cgroups);
        raxSeek(&ri,"^",NULL,0);
        while(raxNext(&ri)) {
            streamCG *cg = ri.data;
            addReplyMapLen(c,6);
            addReplyBulkCString(c,"name");
            addReplyBulkCBuffer(c,ri.key,ri.key_len);
            addReplyBulkCString(c,"consumers");
            addReplyLongLong(c,raxSize(cg->consumers));
            addReplyBulkCString(c,"pending");
            addReplyLongLong(c,raxSize(cg->pel));
            addReplyBulkCString(c,"last-delivered-id");
            addReplyStreamID(c,&cg->last_id);
            addReplyBulkCString(c,"entries-read");
            if (cg->entries_read != SCG_INVALID_ENTRIES_READ) {
                addReplyLongLong(c,cg->entries_read);
            } else {
                addReplyNull(c);
            }
            addReplyBulkCString(c,"lag");
            streamReplyWithCGLag(c,s,cg);
        }
        raxStop(&ri);
    } else if (!strcasecmp(opt,"STREAM")) {

        xinfoReplyWithStreamInfo(c,s);
    } else {
        addReplySubcommandSyntaxError(c);
    }
}
