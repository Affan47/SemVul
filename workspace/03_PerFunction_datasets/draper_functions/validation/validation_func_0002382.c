checkConstantFunctionParameter()
{
    if (!_settings->_checkCodingStyle)
        return;

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::Match(tok, "[,(] const std :: %type% %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(5));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(8));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < std :: %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(10));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < std :: %type% , std :: %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(14));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < %type% , std :: %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(12));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < std :: %type% , %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(12));
        }

        else if (Token::Match(tok, "[,(] const std :: %type% < %type% , %type% > %var% [,)]"))
        {
            passedByValueError(tok, tok->strAt(10));
        }

        else if (Token::Match(tok, "[,(] const %type% %var% [,)]"))
        {

            const std::string pattern(std::string("class|struct ") + tok->strAt(2));
            if (Token::findmatch(_tokenizer->tokens(), pattern.c_str()))
            {
                passedByValueError(tok, tok->strAt(3));
            }
        }
    }
}
