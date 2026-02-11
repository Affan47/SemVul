clear()
{
    QList< Token *> allTokens = tokensAtRow();
    foreach( Token* token, allTokens )
        delete token;
}
