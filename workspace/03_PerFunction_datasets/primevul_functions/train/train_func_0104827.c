static Token *alloc_Token(void)
{
    Token *t = freeTokens;

    if (unlikely(!t)) {
        Token *block;
        size_t i;

        nasm_newn(block, TOKEN_BLOCKSIZE);


        block[0].next = tokenblocks;
	block[0].type = TOK_BLOCK;
        tokenblocks = block;


        for (i = 2; i < TOKEN_BLOCKSIZE - 1; i++)
            block[i].next = &block[i+1];

        freeTokens = &block[2];


        return &block[1];
    }

    freeTokens = t->next;
    t->next = NULL;
    return t;
}
