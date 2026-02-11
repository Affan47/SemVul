yajl_alloc(const yajl_callbacks * callbacks,
           const yajl_parser_config * config,
           const yajl_alloc_funcs * afs,
           void * ctx)
{
    unsigned int allowComments = 0;
    unsigned int validateUTF8 = 0;
    yajl_handle hand = NULL;
    yajl_alloc_funcs afsBuffer;


    if (afs != NULL) {
        if (afs->malloc == NULL || afs->realloc == NULL || afs->free == NULL)
        {
            return NULL;
        }
    } else {
        yajl_set_default_alloc_funcs(&afsBuffer);
        afs = &afsBuffer;
    }

    hand = (yajl_handle) YA_MALLOC(afs, sizeof(struct yajl_handle_t));


    memcpy((void *) &(hand->alloc), (void *) afs, sizeof(yajl_alloc_funcs));

    if (config != NULL) {
        allowComments = config->allowComments;
        validateUTF8 = config->checkUTF8;
    }

    hand->callbacks = callbacks;
    hand->ctx = ctx;
    hand->lexer = yajl_lex_alloc(&(hand->alloc), allowComments, validateUTF8);
    hand->errorOffset = 0;
    hand->decodeBuf = yajl_buf_alloc(&(hand->alloc));
    yajl_bs_init(hand->stateStack, &(hand->alloc));

    yajl_bs_push(hand->stateStack, yajl_state_start);

    return hand;
}
