static Token *steal_Token(Token *dst, Token *src)
{

    memcpy((char *)dst + sizeof(Token *), (char *)src + sizeof(Token *),
	   sizeof(Token) - sizeof(Token *));


    memset((char *)src + sizeof(Token *), 0, sizeof(Token) - sizeof(Token *));

    return dst;
}
