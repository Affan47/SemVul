isConstMemberFunc(const Scope *scope, const Token *tok)
{
    unsigned int args = countParameters(tok);

    std::list<Function>::const_iterator func;
    unsigned int matches = 0;
    unsigned int consts = 0;

    for (func = scope->functionList.begin(); func != scope->functionList.end(); ++func) {


        if (func->tokenDef->str() == tok->str() && (func->argCount() == args || (func->argCount() > args && countMinArgs(func->argDef) <= args))) {
            matches++;
            if (func->isConst)
                consts++;
        }
    }


    if (matches > 0 && matches == consts)
        return true;


    if (!scope->definedType->derivedFrom.empty()) {

        for (unsigned int i = 0; i < scope->definedType->derivedFrom.size(); ++i) {

            const Type *derivedFrom = scope->definedType->derivedFrom[i].type;


            if (derivedFrom && derivedFrom->classScope) {
                if (isConstMemberFunc(derivedFrom->classScope, tok))
                    return true;
            }
        }
    }

    return false;
}
