Node* TY_(GetToken)( TidyDocImpl* doc, GetTokenMode mode )
{
    Node *node;
    Lexer* lexer = doc->lexer;

    if (lexer->pushed || lexer->itoken)
    {

        if (lexer->itoken)
        {

            if (lexer->pushed)
            {
                lexer->pushed = no;
                node = lexer->itoken;
                GTDBG(doc,"lex-itoken", node);
                return node;
            }

            lexer->itoken = NULL;
        }


        lexer->pushed = no;
        if (lexer->token->type != TextNode
            || !(lexer->insert || lexer->inode)) {
            node = lexer->token;
            GTDBG(doc,"lex-token", node);
            return node;
        }
        lexer->itoken = TY_(InsertedToken)( doc );
        node = lexer->itoken;
        GTDBG(doc,"lex-inserted", node);
        return node;
    }

    assert( !(lexer->pushed || lexer->itoken) );


    if (lexer->insert || lexer->inode) {


        lexer->token = TY_(InsertedToken)( doc );
        node = lexer->token;
        GTDBG(doc,"lex-inserted2", node);
        return node;
    }

    if (mode == CdataContent)
    {
        assert( lexer->parent != NULL );
        node = GetCDATA(doc, lexer->parent);
        GTDBG(doc,"lex-cdata", node);
        return node;
    }

    return GetTokenFromStream( doc, mode );
}
