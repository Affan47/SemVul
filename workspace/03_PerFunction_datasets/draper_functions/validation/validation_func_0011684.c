checkBufferAllocatedWithStrlen()
{
    const char pattern[] = "%var% = new|malloc|g_malloc|g_try_malloc|realloc|g_realloc|g_try_realloc";
    for (const Token *tok = Token::findmatch(_tokenizer->tokens(), pattern); tok; tok = Token::findmatch(tok->next(),pattern)) {
        unsigned int dstVarId;
        unsigned int srcVarId;


        if (Token::Match(tok, "%var% = malloc|g_malloc|g_try_malloc ( strlen ( %var% ) )")) {
            dstVarId = tok->varId();
            srcVarId = tok->tokAt(6)->varId();
            tok      = tok->tokAt(8);
        } else if (Token::Match(tok, "%var% = new char [ strlen ( %var% ) ]")) {
            dstVarId = tok->varId();
            srcVarId = tok->tokAt(7)->varId();
            tok      = tok->tokAt(9);
        } else if (Token::Match(tok, "%var% = realloc|g_realloc|g_try_realloc ( %var% , strlen ( %var% ) )")) {
            dstVarId = tok->varId();
            srcVarId = tok->tokAt(8)->varId();
            tok      = tok->tokAt(10);
        } else
            continue;


        for (const Token* const end = tok->scope()->classEnd; tok && tok->next() && tok != end; tok = tok->next()) {

            if (tok->varId() == srcVarId || tok->varId() == dstVarId)
                break;

            if (Token::Match(tok, "strcpy ( %varid% , %var% )", dstVarId) &&
                tok->tokAt(4)->varId() == srcVarId) {
                bufferOverrunError(tok);
            } else if (Token::Match(tok, "sprintf ( %varid% , %str% , %var% )", dstVarId) &&
                       tok->tokAt(6)->varId() == srcVarId &&
                       tok->strAt(4).find("%s") != std::string::npos) {
                bufferOverrunError(tok);
            }

        }

    }
}
