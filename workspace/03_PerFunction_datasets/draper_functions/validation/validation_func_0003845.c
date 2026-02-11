getTemplateNamePosition(const Token *tok)
{

    int namepos = 0;
    if (Token::Match(tok, "> class|struct %type% {|:"))
        namepos = 2;
    else if (Token::Match(tok, "> %type% *|&| %type% ("))
        namepos = 2;
    else if (Token::Match(tok, "> %type% %type% *|&| %type% ("))
        namepos = 3;
    else {

        return -1;
    }
    if ((tok->strAt(namepos) == "*" || tok->strAt(namepos) == "&"))
        ++namepos;

    return namepos;
}
