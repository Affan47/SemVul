uriParseScheme(Parser::Tokenizer &tok)
{


    static const auto schemeChars =
#if USE_HTTP_VIOLATIONS
        CharacterSet("special", "_") +
#endif
        CharacterSet("scheme", "+.-") + CharacterSet::ALPHA + CharacterSet::DIGIT;

    SBuf str;
    if (tok.prefix(str, schemeChars, 16) && tok.skip(':') && CharacterSet::ALPHA[str.at(0)]) {
        const auto protocol = AnyP::UriScheme::FindProtocolType(str);
        if (protocol == AnyP::PROTO_UNKNOWN)
            return AnyP::UriScheme(protocol, str.c_str());
        return AnyP::UriScheme(protocol, nullptr);
    }

    throw TextException("invalid URI scheme", Here());
}
