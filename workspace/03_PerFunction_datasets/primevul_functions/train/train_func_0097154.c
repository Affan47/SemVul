void xaddCommand(client *c) {

    streamAddTrimArgs parsed_args;
    int idpos = streamParseAddOrTrimArgsOrReply(c, &parsed_args, 1);
    if (idpos < 0)
        return;
    int field_pos = idpos+1;


    if ((c->argc - field_pos) < 2 || ((c->argc-field_pos) % 2) == 1) {
        addReplyErrorArity(c);
        return;
    }


    if (parsed_args.id_given && parsed_args.seq_given &&
        parsed_args.id.ms == 0 && parsed_args.id.seq == 0)
    {
        addReplyError(c,"The ID specified in XADD must be greater than 0-0");
        return;
    }


    robj *o;
    stream *s;
    if ((o = streamTypeLookupWriteOrCreate(c,c->argv[1],parsed_args.no_mkstream)) == NULL) return;
    s = o->ptr;


    if (s->last_id.ms == UINT64_MAX && s->last_id.seq == UINT64_MAX) {
        addReplyError(c,"The stream has exhausted the last possible ID, "
                        "unable to add more items");
        return;
    }


    streamID id;
    if (streamAppendItem(s,c->argv+field_pos,(c->argc-field_pos)/2,
        &id,parsed_args.id_given ? &parsed_args.id : NULL,parsed_args.seq_given) == C_ERR)
    {
        if (errno == EDOM)
            addReplyError(c,"The ID specified in XADD is equal or smaller than "
                            "the target stream top item");
        else
            addReplyError(c,"Elements are too large to be stored");
        return;
    }
    sds replyid = createStreamIDString(&id);
    addReplyBulkCBuffer(c, replyid, sdslen(replyid));

    signalModifiedKey(c,c->db,c->argv[1]);
    notifyKeyspaceEvent(NOTIFY_STREAM,"xadd",c->argv[1],c->db->id);
    server.dirty++;


    if (parsed_args.trim_strategy != TRIM_STRATEGY_NONE) {
        if (streamTrim(s, &parsed_args)) {
            notifyKeyspaceEvent(NOTIFY_STREAM,"xtrim",c->argv[1],c->db->id);
        }
        if (parsed_args.approx_trim) {


            streamRewriteApproxSpecifier(c,parsed_args.trim_strategy_arg_idx-1);
            streamRewriteTrimArgument(c,s,parsed_args.trim_strategy,parsed_args.trim_strategy_arg_idx);
        }
    }


    if (!parsed_args.id_given || !parsed_args.seq_given) {
        robj *idarg = createObject(OBJ_STRING, replyid);
        rewriteClientCommandArgument(c, idpos, idarg);
        decrRefCount(idarg);
    } else {
        sdsfree(replyid);
    }


    signalKeyAsReady(c->db, c->argv[1], OBJ_STREAM);
}
