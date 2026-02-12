static Node* GetTokenFromStream( TidyDocImpl* doc, GetTokenMode mode )
{
    Lexer* lexer = doc->lexer;
    uint c, lexdump, badcomment = 0;
    Bool isempty = no;
    AttVal *attributes = NULL;
    Node *node;


    lexer->token = NULL;

    SetLexerLocus( doc, lexer );
    lexer->waswhite = no;

    lexer->txtstart = lexer->txtend = lexer->lexsize;

    while ((c = TY_(ReadChar)(doc->docIn)) != EndOfStream)
    {
        if (lexer->insertspace)
        {
            TY_(AddCharToLexer)(lexer, ' ');
            lexer->waswhite = yes;
            lexer->insertspace = no;
        }

        if (c == 160 && (mode == Preformatted))
            c = ' ';

        TY_(AddCharToLexer)(lexer, c);

        switch (lexer->state)
        {
            case LEX_CONTENT:


                if (TY_(IsWhite)(c) && (mode == IgnoreWhitespace)
                      && lexer->lexsize == lexer->txtstart + 1)
                {
                    --(lexer->lexsize);
                    lexer->waswhite = no;
                    SetLexerLocus( doc, lexer );
                    continue;
                }

                if (c == '<')
                {
                    lexer->state = LEX_GT;
                    continue;
                }

                if (TY_(IsWhite)(c))
                {

                    if (lexer->waswhite)
                    {
                        if (mode != Preformatted && mode != IgnoreMarkup)
                        {
                            --(lexer->lexsize);
                            SetLexerLocus( doc, lexer );
                        }
                    }
                    else
                    {
                        lexer->waswhite = yes;

                        if (mode != Preformatted && mode != IgnoreMarkup && c != ' ')
                            ChangeChar(lexer, ' ');
                    }

                    continue;
                }
                else if (c == '&' && mode != IgnoreMarkup)
                    ParseEntity( doc, mode );


                if (mode == IgnoreWhitespace)
                    mode = MixedContent;

                lexer->waswhite = no;
                continue;

            case LEX_GT:


                if (c == '/')
                {
                    if ((c = TY_(ReadChar)(doc->docIn)) == EndOfStream)
                    {
                        TY_(UngetChar)(c, doc->docIn);
                        continue;
                    }

                    TY_(AddCharToLexer)(lexer, c);

                    if (TY_(IsLetter)(c))
                    {
                        lexer->lexsize -= 3;
                        lexer->txtend = lexer->lexsize;
                        TY_(UngetChar)(c, doc->docIn);
                        lexer->state = LEX_ENDTAG;
                        lexer->lexbuf[lexer->lexsize] = '\0';
                        doc->docIn->curcol -= 2;


                        if (lexer->txtend > lexer->txtstart)
                        {

                            if (mode == IgnoreWhitespace && lexer->lexbuf[lexer->lexsize - 1] == ' ')
                            {
                                lexer->lexsize -= 1;
                                lexer->txtend = lexer->lexsize;
                            }
                            lexer->token = TY_(TextToken)(lexer);
#ifdef TIDY_STORE_ORIGINAL_TEXT
                            StoreOriginalTextInToken(doc, lexer->token, 3);
#endif
                            node = lexer->token;
                            GTDBG(doc,"text", node);
                            return node;
                        }

                        continue;
                    }


                    lexer->waswhite = no;
                    lexer->state = LEX_CONTENT;
                    continue;
                }

                if (mode == IgnoreMarkup)
                {

                    lexer->waswhite = no;
                    lexer->state = LEX_CONTENT;
                    continue;
                }


                if (c == '!')
                {
                    c = TY_(ReadChar)(doc->docIn);

                    if (c == '-')
                    {
                        c = TY_(ReadChar)(doc->docIn);

                        if (c == '-')
                        {
                            lexer->state = LEX_COMMENT;
                            lexer->lexsize -= 2;
                            lexer->txtend = lexer->lexsize;

                            CondReturnTextNode(doc, 4)

                            lexer->txtstart = lexer->lexsize;
                            continue;
                        }

                        TY_(ReportError)(doc, NULL, NULL, MALFORMED_COMMENT );
                    }
                    else if (c == 'd' || c == 'D')
                    {


                        uint skip = 0;

                        lexer->state = LEX_DOCTYPE;
                        lexer->lexsize -= 2;
                        lexer->txtend = lexer->lexsize;
                        mode = IgnoreWhitespace;


                        for (;;)
                        {
                            c = TY_(ReadChar)(doc->docIn);
                            ++skip;

                            if (c == EndOfStream || c == '>')
                            {
                                TY_(UngetChar)(c, doc->docIn);
                                break;
                            }


                            if (!TY_(IsWhite)(c))
                                continue;


                            for (;;)
                            {
                                c = TY_(ReadChar)(doc->docIn);
                                ++skip;

                                if (c == EndOfStream || c == '>')
                                {
                                    TY_(UngetChar)(c, doc->docIn);
                                    break;
                                }


                                if (TY_(IsWhite)(c))
                                    continue;

                                TY_(UngetChar)(c, doc->docIn);
                                break;
                            }

                            break;
                        }

                        CondReturnTextNode(doc, (skip + 3))

                        lexer->txtstart = lexer->lexsize;
                        continue;
                    }
                    else if (c == '[')
                    {

                        lexer->lexsize -= 2;
                        lexer->state = LEX_SECTION;
                        lexer->txtend = lexer->lexsize;

                        CondReturnTextNode(doc, 2)

                        lexer->txtstart = lexer->lexsize;
                        continue;
                    }


                    while ((c = TY_(ReadChar)(doc->docIn)) != '>')
                    {
                        if (c == EndOfStream)
                        {
                            TY_(UngetChar)(c, doc->docIn);
                            break;
                        }
                    }

                    lexer->lexsize -= 2;
                    lexer->lexbuf[lexer->lexsize] = '\0';
                    lexer->state = LEX_CONTENT;
                    continue;
                }


                if (c == '?')
                {
                    lexer->lexsize -= 2;
                    lexer->state = LEX_PROCINSTR;
                    lexer->txtend = lexer->lexsize;

                    CondReturnTextNode(doc, 2)

                    lexer->txtstart = lexer->lexsize;
                    continue;
                }


                if (c == '%')
                {
                    lexer->lexsize -= 2;
                    lexer->state = LEX_ASP;
                    lexer->txtend = lexer->lexsize;

                    CondReturnTextNode(doc, 2)

                    lexer->txtstart = lexer->lexsize;
                    continue;
                }


                if (c == '#')
                {
                    lexer->lexsize -= 2;
                    lexer->state = LEX_JSTE;
                    lexer->txtend = lexer->lexsize;

                    CondReturnTextNode(doc, 2)

                    lexer->txtstart = lexer->lexsize;
                    continue;
                }


                if (TY_(IsLetter)(c))
                {
                    TY_(UngetChar)(c, doc->docIn);
                    TY_(UngetChar)('<', doc->docIn);
                    lexer->lexsize -= 2;
                    lexer->txtend = lexer->lexsize;
                    lexer->state = LEX_STARTTAG;

                    CondReturnTextNode(doc, 2)


                    continue;
                }


                if (c == '&')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    --(lexer->lexsize);
                }


                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                continue;

            case LEX_ENDTAG:
                lexer->txtstart = lexer->lexsize - 1;
                doc->docIn->curcol += 2;
                c = ParseTagName( doc );
                lexer->token = TagToken( doc, EndTag );
                lexer->lexsize = lexer->txtend = lexer->txtstart;


                while ( c != '>' && c != EndOfStream )
                {
                    c = TY_(ReadChar)(doc->docIn);
                }

                if (c == EndOfStream)
                {
                    TY_(FreeNode)( doc, lexer->token );
                    continue;
                }

                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
#ifdef TIDY_STORE_ORIGINAL_TEXT
                StoreOriginalTextInToken(doc, lexer->token, 0);
#endif
                node = lexer->token;
                GTDBG(doc,"endtag", node);
                return node;

            case LEX_STARTTAG:
                c = TY_(ReadChar)(doc->docIn);
                ChangeChar(lexer, (tmbchar)c);
                lexer->txtstart = lexer->lexsize - 1;
                c = ParseTagName( doc );
                isempty = no;
                attributes = NULL;
                lexer->token = TagToken( doc, StartTag );


                if (c != '>')
                {
                    if (c == '/')
                        TY_(UngetChar)(c, doc->docIn);

                    attributes = ParseAttrs( doc, &isempty );
                }

                if (isempty)
                    lexer->token->type = StartEndTag;

                lexer->token->attributes = attributes;
                lexer->lexsize = lexer->txtend = lexer->txtstart;


                if ((mode != Preformatted && ExpectsContent(lexer->token))
                    || nodeIsBR(lexer->token) || nodeIsHR(lexer->token))
                {
                    c = TY_(ReadChar)(doc->docIn);

                    if (c != '\n' && c != '\f')
                        TY_(UngetChar)(c, doc->docIn);

                    lexer->waswhite = yes;
                }
                else
                    lexer->waswhite = no;

                lexer->state = LEX_CONTENT;
                if (lexer->token->tag == NULL)
                {
                    if (mode != OtherNamespace)
                        TY_(ReportFatal)( doc, NULL, lexer->token, UNKNOWN_ELEMENT );
                }
                else if ( !cfgBool(doc, TidyXmlTags) )
                {
                    Node* curr = lexer->token;
                    TY_(ConstrainVersion)( doc, curr->tag->versions );

                    if ( curr->tag->versions & VERS_PROPRIETARY )
                    {
                        if ( !cfgBool(doc, TidyMakeClean) ||
                             ( !nodeIsNOBR(curr) && !nodeIsWBR(curr) ) )
                        {
                            TY_(ReportError)(doc, NULL, curr, PROPRIETARY_ELEMENT );

                            if ( nodeIsLAYER(curr) )
                                doc->badLayout |= USING_LAYER;
                            else if ( nodeIsSPACER(curr) )
                                doc->badLayout |= USING_SPACER;
                            else if ( nodeIsNOBR(curr) )
                                doc->badLayout |= USING_NOBR;
                        }
                    }

                    TY_(RepairDuplicateAttributes)( doc, curr, no );
                } else
                    TY_(RepairDuplicateAttributes)( doc, lexer->token, yes );
#ifdef TIDY_STORE_ORIGINAL_TEXT
                StoreOriginalTextInToken(doc, lexer->token, 0);
#endif
                node = lexer->token;
                GTDBG(doc,"starttag", node);
                return node;

            case LEX_COMMENT:

                if (c != '-')
                    continue;

                c = TY_(ReadChar)(doc->docIn);
                TY_(AddCharToLexer)(lexer, c);

                if (c != '-')
                    continue;

            end_comment:
                c = TY_(ReadChar)(doc->docIn);

                if (c == '>')
                {
                    if (badcomment)
                        TY_(ReportError)(doc, NULL, NULL, MALFORMED_COMMENT );


                    lexer->lexsize -= 2;
                    lexer->txtend = lexer->lexsize;
                    lexer->lexbuf[lexer->lexsize] = '\0';
                    lexer->state = LEX_CONTENT;
                    lexer->waswhite = no;
                    lexer->token = CommentToken(doc);


                    c = TY_(ReadChar)(doc->docIn);

                    if (c == '\n')
                        lexer->token->linebreak = yes;
                    else
                        TY_(UngetChar)(c, doc->docIn);

                    node = lexer->token;
                    GTDBG(doc,"comment", node);
                    return node;
                }


                if (!badcomment)
                {
                    SetLexerLocus( doc, lexer );
                    lexer->columns -= 3;
                }

                badcomment++;

                if ( cfgBool(doc, TidyFixComments) )
                    lexer->lexbuf[lexer->lexsize - 2] = '=';


                if (c == '-')
                {
                    TY_(AddCharToLexer)(lexer, c);
                    goto end_comment;
                }


                lexer->lexbuf[lexer->lexsize - 1] = '=';


                TY_(AddCharToLexer)(lexer, c);

                continue;

            case LEX_DOCTYPE:


                TY_(UngetChar)(c, doc->docIn);
                lexer->lexsize -= 1;
                lexer->token = ParseDocTypeDecl(doc);

                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;


                if (lexer->doctype == VERS_UNKNOWN && lexer->token && !cfgBool(doc, TidyXmlTags))
                {
                    lexer->doctype = FindGivenVersion(doc, lexer->token);
                    if (lexer->doctype != VERS_HTML5)
                    {


                        TY_(AdjustTags)(doc);
                    }
                }
                node = lexer->token;
                GTDBG(doc,"doctype", node);
                return node;

            case LEX_PROCINSTR:


                if  (lexer->lexsize - lexer->txtstart == 3)
                {
                    if (TY_(tmbstrncmp)(lexer->lexbuf + lexer->txtstart, "php", 3) == 0)
                    {
                        lexer->state = LEX_PHP;
                        continue;
                    }
                }

                if  (lexer->lexsize - lexer->txtstart == 4)
                {
                    if (TY_(tmbstrncmp)(lexer->lexbuf + lexer->txtstart, "xml", 3) == 0 &&
                        TY_(IsWhite)(lexer->lexbuf[lexer->txtstart + 3]))
                    {
                        lexer->state = LEX_XMLDECL;
                        attributes = NULL;
                        continue;
                    }
                }

                if (cfgBool(doc, TidyXmlPIs) || lexer->isvoyager)
                {
                    if (c != '?')
                        continue;


                    c = TY_(ReadChar)(doc->docIn);

                    if (c == EndOfStream)
                    {
                        TY_(ReportError)(doc, NULL, NULL, UNEXPECTED_END_OF_FILE );
                        TY_(UngetChar)(c, doc->docIn);
                        continue;
                    }

                    TY_(AddCharToLexer)(lexer, c);
                }


                if (c != '>')
                    continue;

                lexer->lexsize -= 1;

                if (lexer->lexsize)
                {
                    uint i;
                    Bool closed;

                    for (i = 0; i < lexer->lexsize - lexer->txtstart &&
                        !TY_(IsWhite)(lexer->lexbuf[i + lexer->txtstart]); ++i)
                        ;

                    closed = lexer->lexbuf[lexer->lexsize - 1] == '?';

                    if (closed)
                        lexer->lexsize -= 1;

                    lexer->txtstart += i;
                    lexer->txtend = lexer->lexsize;
                    lexer->lexbuf[lexer->lexsize] = '\0';

                    lexer->token = PIToken(doc);
                    lexer->token->closed = closed;
                    lexer->token->element = TY_(tmbstrndup)(doc->allocator,
                                                            lexer->lexbuf +
                                                            lexer->txtstart - i, i);
                }
                else
                {
                    lexer->txtend = lexer->lexsize;
                    lexer->lexbuf[lexer->lexsize] = '\0';
                    lexer->token = PIToken(doc);
                }

                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                node = lexer->token;
                GTDBG(doc,"procinstr", node);
                return node;

            case LEX_ASP:
                if (c != '%')
                    continue;


                c = TY_(ReadChar)(doc->docIn);


                if (c != '>')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }

                lexer->lexsize -= 1;
                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = AspToken(doc);
                node = lexer->token;
                GTDBG(doc,"ASP", node);
                return node;


            case LEX_JSTE:
                if (c != '#')
                    continue;


                c = TY_(ReadChar)(doc->docIn);


                if (c != '>')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }

                lexer->lexsize -= 1;
                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = JsteToken(doc);
                node = lexer->token;
                GTDBG(doc,"JSTE", node);
                return node;


            case LEX_PHP:
                if (c != '?')
                    continue;


                c = TY_(ReadChar)(doc->docIn);

                if (c != '>')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }

                lexer->lexsize -= 1;
                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = PhpToken(doc);
                node = lexer->token;
                GTDBG(doc,"PHP", node);
                return node;

            case LEX_XMLDECL:

                if (TY_(IsWhite)(c) && c != '?')
                    continue;


                if (c != '?')
                {
                    tmbstr name;
                    Node *asp, *php;
                    AttVal *av = NULL;
                    int pdelim = 0;
                    isempty = no;

                    TY_(UngetChar)(c, doc->docIn);

                    name = ParseAttribute( doc, &isempty, &asp, &php );

                    if (!name)
                    {

                        lexer->lexsize -= 1;
                        lexer->txtend = lexer->txtstart;
                        lexer->lexbuf[lexer->txtend] = '\0';
                        lexer->state = LEX_CONTENT;
                        lexer->waswhite = no;
                        lexer->token = XmlDeclToken(doc);
                        lexer->token->attributes = attributes;
                        node = lexer->token;
                        GTDBG(doc,"xml", node);
                        return node;
                    }

                    av = TY_(NewAttribute)(doc);
                    av->attribute = name;
                    av->value = ParseValue( doc, name, yes, &isempty, &pdelim );
                    av->delim = pdelim;
                    av->dict = TY_(FindAttribute)( doc, av );

                    AddAttrToList( &attributes, av );

                }


                c = TY_(ReadChar)(doc->docIn);

                if (c != '>')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }
                lexer->lexsize -= 1;
                lexer->txtend = lexer->txtstart;
                lexer->lexbuf[lexer->txtend] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = XmlDeclToken(doc);
                lexer->token->attributes = attributes;
                node = lexer->token;
                GTDBG(doc,"XML", node);
                return node;

            case LEX_SECTION:
                if (c == '[')
                {
                    if (lexer->lexsize == (lexer->txtstart + 6) &&
                        TY_(tmbstrncmp)(lexer->lexbuf+lexer->txtstart, "CDATA[", 6) == 0)
                    {
                        lexer->state = LEX_CDATA;
                        lexer->lexsize -= 6;
                        continue;
                    }
                }

                if (c != ']')
                    continue;


                c = TY_(ReadChar)(doc->docIn);

                lexdump = 1;
                if (c != '>')
                {

                    if (c == '-')
                    {
                        c = TY_(ReadChar)(doc->docIn);
                        if (c == '-')
                        {
                            c = TY_(ReadChar)(doc->docIn);
                            if (c != '>')
                            {
                                TY_(UngetChar)(c, doc->docIn);
                                TY_(UngetChar)('-', doc->docIn);
                                TY_(UngetChar)('-', doc->docIn);
                                continue;
                            }


                        }
                        else
                        {
                            TY_(UngetChar)(c, doc->docIn);
                            TY_(UngetChar)('-', doc->docIn);
                            continue;
                        }
                    }
                    else
                    {
                        TY_(UngetChar)(c, doc->docIn);
                        continue;
                    }
                }

                lexer->lexsize -= lexdump;
                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = SectionToken(doc);
                node = lexer->token;
                GTDBG(doc,"SECTION", node);
                return node;

            case LEX_CDATA:
                if (c != ']')
                    continue;


                c = TY_(ReadChar)(doc->docIn);

                if (c != ']')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    continue;
                }


                c = TY_(ReadChar)(doc->docIn);

                if (c != '>')
                {
                    TY_(UngetChar)(c, doc->docIn);
                    TY_(UngetChar)(']', doc->docIn);
                    continue;
                }

                lexer->lexsize -= 1;
                lexer->txtend = lexer->lexsize;
                lexer->lexbuf[lexer->lexsize] = '\0';
                lexer->state = LEX_CONTENT;
                lexer->waswhite = no;
                lexer->token = CDATAToken(doc);
                node = lexer->token;
                GTDBG(doc,"CDATA", node);
                return node;
        }
    }

    if (lexer->state == LEX_CONTENT)
    {
        lexer->txtend = lexer->lexsize;

        if (lexer->txtend > lexer->txtstart)
        {
            TY_(UngetChar)(c, doc->docIn);

            if (lexer->lexbuf[lexer->lexsize - 1] == ' ')
            {
                lexer->lexsize -= 1;
                lexer->txtend = lexer->lexsize;
            }
            lexer->token = TY_(TextToken)(lexer);
#ifdef TIDY_STORE_ORIGINAL_TEXT
            StoreOriginalTextInToken(doc, lexer->token, 0);
#endif
            node = lexer->token;
            GTDBG(doc,"textstring", node);
            return node;
        }
    }
    else if (lexer->state == LEX_COMMENT)
    {
        if (c == EndOfStream)
            TY_(ReportError)(doc, NULL, NULL, MALFORMED_COMMENT );

        lexer->txtend = lexer->lexsize;
        lexer->lexbuf[lexer->lexsize] = '\0';
        lexer->state = LEX_CONTENT;
        lexer->waswhite = no;
        lexer->token = CommentToken(doc);
        node = lexer->token;
        GTDBG(doc,"COMMENT", node);
        return node;
    }

#if !defined(NDEBUG) && defined(_MSC_VER)
    SPRTF("Returning NULL...\n");
#endif
    return NULL;
}
