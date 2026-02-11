invalidFunctionUsage()
{

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if ((tok->str() != "strtol") && (tok->str() != "strtoul"))
            continue;


        int parlevel = 0;
        int param = 1;
        for (const Token *tok2 = tok->next(); tok2; tok2 = tok2->next())
        {
            if (tok2->str() == "(")
                ++parlevel;
            else if (tok2->str() == ")")
                --parlevel;
            else if (parlevel == 1 && tok2->str() == ",")
            {
                ++param;
                if (param == 3)
                {
                    if (Token::Match(tok2, ", %num% )"))
                    {
                        const MathLib::bigint radix = MathLib::toLongNumber(tok2->next()->str());
                        if (!(radix == 0 || (radix >= 2 && radix <= 36)))
                        {
                            dangerousUsageStrtolError(tok2);
                        }
                    }
                    break;
                }
            }
        }
    }


    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {

        unsigned int varid = 0;

        if (Token::Match(tok, "sprintf|snprintf ( %var% ,"))
            varid = tok->tokAt(2)->varId();

        else if (Token::Match(tok, "sprintf|snprintf ( %var% . %var% ,"))
            varid = tok->tokAt(4)->varId();

        if (varid == 0)
            continue;


        const Token *tok2 = tok->tokAt(3);
        while (tok2 && tok2->str() != ",")
            tok2 = tok2->next();


        int parlevel = 0;
        while ((tok2 = tok2->next()) != NULL)
        {
            if (tok2->str() == "(")
                ++parlevel;
            else if (tok2->str() == ")")
            {
                --parlevel;
                if (parlevel < 0)
                    break;
            }
            else if (parlevel == 0 && Token::Match(tok2, ", %varid% [,)]", varid))
            {
                sprintfOverlappingDataError(tok2->next(), tok2->next()->str());
                break;
            }
        }
    }
}
