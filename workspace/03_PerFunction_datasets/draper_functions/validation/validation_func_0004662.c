checkModuloAlwaysTrueFalse()
{
    if (!_settings->isEnabled("warning"))
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if (!tok->isComparisonOp())
                continue;
            const Token *num, *modulo;
            if (Token::simpleMatch(tok->astOperand1(), "%") && Token::Match(tok->astOperand2(), "%num%")) {
                modulo = tok->astOperand1();
                num = tok->astOperand2();
            } else if (Token::Match(tok->astOperand1(), "%num%") && Token::simpleMatch(tok->astOperand2(), "%")) {
                num = tok->astOperand1();
                modulo = tok->astOperand2();
            } else {
                continue;
            }

            if (Token::Match(modulo->astOperand2(), "%num%") &&
                MathLib::isLessEqual(modulo->astOperand2()->str(), num->str()))
                moduloAlwaysTrueFalseError(tok, modulo->astOperand2()->str());
        }
    }
}
