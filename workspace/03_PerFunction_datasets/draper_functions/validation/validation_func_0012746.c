checkSleepTimeInterval()
{
    if (!_settings->standards.posix)
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if (Token::Match(tok, "usleep ( %num% )")) {
                const Token * const numTok = tok->tokAt(2);
                MathLib::bigint value = MathLib::toLongNumber(numTok->str());
                if (value > 999999) {
                    checkSleepTimeError(numTok, numTok->str());
                }
            }
        }
    }
}
