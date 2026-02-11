returncstr()
{


    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();

    std::list<Scope>::const_iterator scope;

    for (scope = symbolDatabase->scopeList.begin(); scope != symbolDatabase->scopeList.end(); ++scope) {

        if (scope->type != Scope::eFunction || !scope->function)
            continue;

        const Token *tok = scope->function->tokenDef;


        if (Token::simpleMatch(tok->tokAt(-3), "const char *")) {
            for (const Token *tok2 = scope->classStart; tok2 && tok2 != scope->classEnd; tok2 = tok2->next()) {

                if (returnTemporary(tok2)) {

                    errorReturnTempPointer(tok2);
                }
            }
        }
    }
}
