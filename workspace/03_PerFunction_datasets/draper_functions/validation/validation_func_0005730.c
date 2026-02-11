writeOutsideBufferSize()
{
    if (!_settings->standards.posix)
        return;

    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * const scope = symbolDatabase->functionScopes[i];
        for (const Token *tok = scope->classStart; tok && tok != scope->classEnd; tok = tok->next()) {
            if (Token::Match(tok, "pwrite|write (") && Token::Match(tok->tokAt(2)->nextArgument(), "%str% , %num%")) {
                const std::string & functionName(tok->str());
                tok = tok->tokAt(2)->nextArgument();
                const std::size_t stringLength = Token::getStrLength(tok)+1;
                tok = tok->tokAt(2);
                const MathLib::bigint writeLength = MathLib::toLongNumber(tok->str());
                if (static_cast<std::size_t>(writeLength) > stringLength)
                    writeOutsideBufferSizeError(tok, stringLength, writeLength, functionName);
            }
        }
    }
}
