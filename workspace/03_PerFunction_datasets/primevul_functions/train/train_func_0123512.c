static Node *GetCDATA( TidyDocImpl* doc, Node *container )
{
    Lexer* lexer = doc->lexer;
    uint start = 0;
    int nested = 0;
    CDATAState state = CDATA_INTERMEDIATE;
    uint i;
    Bool isEmpty = yes;
    Bool matches = no;
    uint c;
    Bool hasSrc = TY_(AttrGetById)(container, TidyAttr_SRC) != NULL;

    SetLexerLocus( doc, lexer );
    lexer->waswhite = no;
    lexer->txtstart = lexer->txtend = lexer->lexsize;


    while ((c = TY_(ReadChar)(doc->docIn)) != EndOfStream)
    {
        TY_(AddCharToLexer)(lexer, c);
        lexer->txtend = lexer->lexsize;

        if (state == CDATA_INTERMEDIATE)
        {
            if (c != '<')
            {
                if (isEmpty && !TY_(IsWhite)(c))
                    isEmpty = no;
                continue;
            }

            c = TY_(ReadChar)(doc->docIn);

            if (TY_(IsLetter)(c))
            {

                if (hasSrc && isEmpty && nodeIsSCRIPT(container))
                {

                    lexer->lexsize = lexer->txtstart;
                    TY_(UngetChar)(c, doc->docIn);
                    TY_(UngetChar)('<', doc->docIn);
                    return NULL;
                }
                TY_(AddCharToLexer)(lexer, c);
                start = lexer->lexsize - 1;
                state = CDATA_STARTTAG;
            }
            else if (c == '/')
            {
                TY_(AddCharToLexer)(lexer, c);

                c = TY_(ReadChar)(doc->docIn);

                if (!TY_(IsLetter)(c))
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }
                TY_(UngetChar)(c, doc->docIn);

                start = lexer->lexsize;
                state = CDATA_ENDTAG;
            }
            else if (c == '\\')
            {

                TY_(AddCharToLexer)(lexer, c);

                c = TY_(ReadChar)(doc->docIn);

                if (c != '/')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }

                TY_(AddCharToLexer)(lexer, c);
                c = TY_(ReadChar)(doc->docIn);

                if (!TY_(IsLetter)(c))
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }
                TY_(UngetChar)(c, doc->docIn);

                start = lexer->lexsize;
                state = CDATA_ENDTAG;
            }
            else
            {
                TY_(UngetChar)(c, doc->docIn);
            }
        }

        else if (state == CDATA_STARTTAG)
        {
            if (TY_(IsLetter)(c))
                continue;

            matches = TY_(tmbstrncasecmp)(container->element, lexer->lexbuf + start,
                                          TY_(tmbstrlen)(container->element)) == 0;
            if (matches)
                nested++;

            state = CDATA_INTERMEDIATE;
        }

        else if (state == CDATA_ENDTAG)
        {
            if (TY_(IsLetter)(c))
                continue;

            matches = TY_(tmbstrncasecmp)(container->element, lexer->lexbuf + start,
                                          TY_(tmbstrlen)(container->element)) == 0;

            if (isEmpty && !matches)
            {


                for (i = lexer->lexsize - 1; i >= start; --i)
                    TY_(UngetChar)((uint)lexer->lexbuf[i], doc->docIn);
                TY_(UngetChar)('/', doc->docIn);
                TY_(UngetChar)('<', doc->docIn);
                break;
            }

            if (matches && nested-- <= 0)
            {
                for (i = lexer->lexsize - 1; i >= start; --i)
                    TY_(UngetChar)((uint)lexer->lexbuf[i], doc->docIn);
                TY_(UngetChar)('/', doc->docIn);
                TY_(UngetChar)('<', doc->docIn);
                lexer->lexsize -= (lexer->lexsize - start) + 2;
                break;
            }
            else if (lexer->lexbuf[start - 2] != '\\')
            {

                SetLexerLocus( doc, lexer );
                lexer->columns -= 3;
                TY_(ReportError)(doc, NULL, NULL, BAD_CDATA_CONTENT);


                if (TY_(IsJavaScript)(container))
                {
                    for (i = lexer->lexsize; i > start-1; --i)
                        lexer->lexbuf[i] = lexer->lexbuf[i-1];

                    lexer->lexbuf[start-1] = '\\';
                    lexer->lexsize++;
                }
            }
            state = CDATA_INTERMEDIATE;
        }
    }
    if (isEmpty)
        lexer->lexsize = lexer->txtstart = lexer->txtend;
    else
        lexer->txtend = lexer->lexsize;

    if (c == EndOfStream)
        TY_(ReportError)(doc, container, NULL, MISSING_ENDTAG_FOR );


#if 0
    if (lexer->txtend > lexer->txtstart)
        return TextToken(lexer);
    else
        return NULL;
#else
    return TY_(TextToken)(lexer);
#endif
}
