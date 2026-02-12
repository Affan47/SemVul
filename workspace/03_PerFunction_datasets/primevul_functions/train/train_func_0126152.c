AnyP::Uri::Encode(const SBuf &buf, const CharacterSet &ignore)
{
    if (buf.isEmpty())
        return buf;

    Parser::Tokenizer tk(buf);
    SBuf goodSection;

    if (tk.prefix(goodSection, ignore) && tk.atEnd())
        return buf;

    SBuf output;
    output.reserveSpace(buf.length() * 3);
    output.append(goodSection);

    while (!tk.atEnd()) {

        const auto ch = tk.remaining()[0];
        output.appendf("%%%02X", static_cast<unsigned int>(ch));
        (void)tk.skip(ch);

        if (tk.prefix(goodSection, ignore))
            output.append(goodSection);
    }

    return output;
}
