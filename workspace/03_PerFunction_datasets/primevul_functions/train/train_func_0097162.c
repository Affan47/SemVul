void xtrimCommand(client *c) {
    robj *o;


    streamAddTrimArgs parsed_args;
    if (streamParseAddOrTrimArgsOrReply(c, &parsed_args, 0) < 0)
        return;


    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL
        || checkType(c,o,OBJ_STREAM)) return;
    stream *s = o->ptr;


    int64_t deleted = streamTrim(s, &parsed_args);
    if (deleted) {
        notifyKeyspaceEvent(NOTIFY_STREAM,"xtrim",c->argv[1],c->db->id);
        if (parsed_args.approx_trim) {


            streamRewriteApproxSpecifier(c,parsed_args.trim_strategy_arg_idx-1);
            streamRewriteTrimArgument(c,s,parsed_args.trim_strategy,parsed_args.trim_strategy_arg_idx);
        }


        signalModifiedKey(c, c->db,c->argv[1]);
        server.dirty += deleted;
    }
    addReplyLongLong(c,deleted);
}
