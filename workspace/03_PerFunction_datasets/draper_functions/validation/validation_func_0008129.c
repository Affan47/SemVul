HandleUnDef (Token &iBody, int iLine)
{
    CPreprocessor cpp (iBody, iLine);

    Token t = cpp.GetToken (false);

    if (t.Type != Token::TK_KEYWORD)
    {
        Error (iLine, "Expecting a macro name after #undef, got", &t);
        return false;
    }


    Undef (t.String, t.Length);

    do
    {
        t = cpp.GetToken (false);
    } while (t.Type == Token::TK_WHITESPACE ||
             t.Type == Token::TK_COMMENT ||
             t.Type == Token::TK_LINECOMMENT);

    if (t.Type != Token::TK_EOS)
        Error (iLine, "Warning: Ignoring garbage after directive", &t);

    return true;
}
