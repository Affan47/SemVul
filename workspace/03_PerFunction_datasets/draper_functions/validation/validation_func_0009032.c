checkConstantFunctionParameter()
{
    if (!_settings->isEnabled("performance") || _tokenizer->isC())
        return;

    const SymbolDatabase * const symbolDatabase = _tokenizer->getSymbolDatabase();

    for (unsigned int i = 1; i < symbolDatabase->getVariableListSize(); i++) {
        const Variable* var = symbolDatabase->getVariableFromVarId(i);
        if (!var || !var->isArgument() || !var->isClass() || !var->isConst() || var->isPointer() || var->isArray() || var->isReference())
            continue;

        if (var->scope() && var->scope()->function->arg->link()->strAt(-1) == ".")
            continue;

        const Token* const tok = var->typeStartToken();


        if (var->isStlStringType()) {
            passedByValueError(tok, var->name());
        } else if (var->isStlType() && Token::Match(tok, "std :: %type% <") && !Token::simpleMatch(tok->linkAt(3), "> ::")) {
            passedByValueError(tok, var->name());
        } else if (var->type()) {
            passedByValueError(tok, var->name());
        }
    }
}
