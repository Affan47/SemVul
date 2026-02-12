static tmbstr ParseValue( TidyDocImpl* doc, ctmbstr name,
                          Bool foldCase, Bool *isempty, int *pdelim)
{
    Lexer* lexer = doc->lexer;
    int len = 0, start;
    Bool seen_gt = no;
    Bool munge = yes;
    uint c, lastc, delim, quotewarning;
    tmbstr value;

    delim = (tmbchar) 0;
    *pdelim = '"';


    if ( cfgBool(doc, TidyLiteralAttribs) )
        munge = no;


    for (;;)
    {
        c = TY_(ReadChar)(doc->docIn);

        if (c == EndOfStream)
        {
            TY_(UngetChar)(c, doc->docIn);
            break;
        }

        if (!TY_(IsWhite)(c))
           break;
    }


    if (c != '=' && c != '"' && c != '\'')
    {
        TY_(UngetChar)(c, doc->docIn);
        return NULL;
    }


    for (;;)
    {
        c = TY_(ReadChar)(doc->docIn);

        if (c == EndOfStream)
        {
            TY_(UngetChar)(c, doc->docIn);
            break;
        }

        if (!TY_(IsWhite)(c))
           break;
    }


    if (c == '"' || c == '\'')
        delim = c;
    else if (c == '<')
    {
        start = lexer->lexsize;
        TY_(AddCharToLexer)(lexer, c);
        *pdelim = ParseServerInstruction( doc );
        len = lexer->lexsize - start;
        lexer->lexsize = start;
        return (len > 0 ? TY_(tmbstrndup)(doc->allocator,
                                          lexer->lexbuf+start, len) : NULL);
    }
    else
        TY_(UngetChar)(c, doc->docIn);


    quotewarning = 0;
    start = lexer->lexsize;
    c = '\0';

    for (;;)
    {
        lastc = c;
        c = TY_(ReadChar)(doc->docIn);

        if (c == EndOfStream)
        {
            TY_(ReportAttrError)( doc, lexer->token, NULL, UNEXPECTED_END_OF_FILE_ATTR );
            TY_(UngetChar)(c, doc->docIn);
            break;
        }

        if (delim == (tmbchar)0)
        {
            if (c == '>')
            {
                TY_(UngetChar)(c, doc->docIn);
                break;
            }

            if (c == '"' || c == '\'')
            {
                uint q = c;

                TY_(ReportAttrError)( doc, lexer->token, NULL, UNEXPECTED_QUOTEMARK );


                c = TY_(ReadChar)(doc->docIn);
                if (c == '>')
                {
                    TY_(AddCharToLexer)(lexer, q);
                    TY_(UngetChar)(c, doc->docIn);
                    break;
                }
                else
                {
                    TY_(UngetChar)(c, doc->docIn);
                    c = q;
                }
            }

            if (c == '<')
            {
                TY_(UngetChar)(c, doc->docIn);
                c = '>';
                TY_(UngetChar)(c, doc->docIn);
                TY_(ReportAttrError)( doc, lexer->token, NULL, UNEXPECTED_GT );
                break;
            }


            if (c == '/')
            {

                c = TY_(ReadChar)(doc->docIn);

                if ( c == '>' && !TY_(IsUrl)(doc, name) )
                {
                    *isempty = yes;
                    TY_(UngetChar)(c, doc->docIn);
                    break;
                }


                TY_(UngetChar)(c, doc->docIn);
                c = '/';
            }
        }
        else
        {
            if (c == delim)
                break;

            if (c == '\n' || c == '<' || c == '>')
                ++quotewarning;

            if (c == '>')
                seen_gt = yes;
        }

        if (c == '&')
        {
            TY_(AddCharToLexer)(lexer, c);
            ParseEntity( doc, IgnoreWhitespace );
            if (lexer->lexbuf[lexer->lexsize - 1] == '\n' && munge)
                ChangeChar(lexer, ' ');
            continue;
        }


        if (c == '\\')
        {
            c = TY_(ReadChar)(doc->docIn);

            if (c != '\n')
            {
                TY_(UngetChar)(c, doc->docIn);
                c = '\\';
            }
        }

        if (TY_(IsWhite)(c))
        {
            if ( delim == 0 )
                break;

            if (munge)
            {


                if ( c == '\n' && TY_(IsUrl)(doc, name) )
                {

                    TY_(ReportAttrError)( doc, lexer->token, NULL, NEWLINE_IN_URI);
                    continue;
                }

                c = ' ';

                if (lastc == ' ')
                {
                    if (TY_(IsUrl)(doc, name) )
                        TY_(ReportAttrError)( doc, lexer->token, NULL, WHITE_IN_URI);
                    continue;
                }
            }
        }
        else if (foldCase && TY_(IsUpper)(c))
            c = TY_(ToLower)(c);

        TY_(AddCharToLexer)(lexer, c);
    }

    if (quotewarning > 10 && seen_gt && munge)
    {


        if ( !TY_(IsScript)(doc, name) &&
             !(TY_(IsUrl)(doc, name) && TY_(tmbstrncmp)(lexer->lexbuf+start, "javascript:", 11) == 0) &&
             !(TY_(tmbstrncmp)(lexer->lexbuf+start, "<xml ", 5) == 0)
           )
            TY_(ReportFatal)( doc, NULL, NULL, SUSPECTED_MISSING_QUOTE );
    }

    len = lexer->lexsize - start;
    lexer->lexsize = start;


    if (len > 0 || delim)
    {


        if (munge &&
            TY_(tmbstrcasecmp)(name, "alt") &&
            TY_(tmbstrcasecmp)(name, "title") &&
            TY_(tmbstrcasecmp)(name, "value") &&
            TY_(tmbstrcasecmp)(name, "prompt"))
        {
            while (TY_(IsWhite)(lexer->lexbuf[start+len-1]))
                --len;

            while (TY_(IsWhite)(lexer->lexbuf[start]) && start < len)
            {
                ++start;
                --len;
            }
        }

        value = TY_(tmbstrndup)(doc->allocator, lexer->lexbuf + start, len);
    }
    else
        value = NULL;


    *pdelim = (delim ? delim : '"');

    return value;
}
