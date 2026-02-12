static int streamParseAddOrTrimArgsOrReply(client *c, streamAddTrimArgs *args, int xadd) {

    memset(args, 0, sizeof(*args));


    int i = 2;

    int limit_given = 0;
    for (; i < c->argc; i++) {
        int moreargs = (c->argc-1) - i;
        char *opt = c->argv[i]->ptr;
        if (xadd && opt[0] == '*' && opt[1] == '\0') {


            break;
        } else if (!strcasecmp(opt,"maxlen") && moreargs) {
            if (args->trim_strategy != TRIM_STRATEGY_NONE) {
                addReplyError(c,"syntax error, MAXLEN and MINID options at the same time are not compatible");
                return -1;
            }
            args->approx_trim = 0;
            char *next = c->argv[i+1]->ptr;

            if (moreargs >= 2 && next[0] == '~' && next[1] == '\0') {
                args->approx_trim = 1;
                i++;
            } else if (moreargs >= 2 && next[0] == '=' && next[1] == '\0') {
                i++;
            }
            if (getLongLongFromObjectOrReply(c,c->argv[i+1],&args->maxlen,NULL)
                != C_OK) return -1;

            if (args->maxlen < 0) {
                addReplyError(c,"The MAXLEN argument must be >= 0.");
                return -1;
            }
            i++;
            args->trim_strategy = TRIM_STRATEGY_MAXLEN;
            args->trim_strategy_arg_idx = i;
        } else if (!strcasecmp(opt,"minid") && moreargs) {
            if (args->trim_strategy != TRIM_STRATEGY_NONE) {
                addReplyError(c,"syntax error, MAXLEN and MINID options at the same time are not compatible");
                return -1;
            }
            args->approx_trim = 0;
            char *next = c->argv[i+1]->ptr;

            if (moreargs >= 2 && next[0] == '~' && next[1] == '\0') {
                args->approx_trim = 1;
                i++;
            } else if (moreargs >= 2 && next[0] == '=' && next[1] == '\0') {
                i++;
            }

            if (streamParseStrictIDOrReply(c,c->argv[i+1],&args->minid,0,NULL) != C_OK)
                return -1;

            i++;
            args->trim_strategy = TRIM_STRATEGY_MINID;
            args->trim_strategy_arg_idx = i;
        } else if (!strcasecmp(opt,"limit") && moreargs) {


            if (getLongLongFromObjectOrReply(c,c->argv[i+1],&args->limit,NULL) != C_OK)
                return -1;

            if (args->limit < 0) {
                addReplyError(c,"The LIMIT argument must be >= 0.");
                return -1;
            }
            limit_given = 1;
            i++;
        } else if (xadd && !strcasecmp(opt,"nomkstream")) {
            args->no_mkstream = 1;
        } else if (xadd) {

            if (streamParseStrictIDOrReply(c,c->argv[i],&args->id,0,&args->seq_given) != C_OK)
                return -1;
            args->id_given = 1;
            break;
        } else {
            addReplyErrorObject(c,shared.syntaxerr);
            return -1;
        }
    }

    if (args->limit && args->trim_strategy == TRIM_STRATEGY_NONE) {
        addReplyError(c,"syntax error, LIMIT cannot be used without specifying a trimming strategy");
        return -1;
    }

    if (!xadd && args->trim_strategy == TRIM_STRATEGY_NONE) {
        addReplyError(c,"syntax error, XTRIM must be called with a trimming strategy");
        return -1;
    }

    if (mustObeyClient(c)) {


        args->limit = 0;
    } else {

        if (limit_given) {
            if (!args->approx_trim) {

                addReplyError(c,"syntax error, LIMIT cannot be used without the special ~ option");
                return -1;
            }
        } else {

            if (args->approx_trim) {


                args->limit = 100 * server.stream_node_max_entries;
                if (args->limit <= 0) args->limit = 10000;
                if (args->limit > 1000000) args->limit = 1000000;
            } else {

                args->limit = 0;
            }
        }
    }

    return i;
}
