operatorEqRetRefThis()
{
    if (!_settings->_checkCodingStyle)
        return;

    createSymbolDatabase();

    std::list<SymbolDatabase::SpaceInfo *>::const_iterator i;

    for (i = symbolDatabase->spaceInfoList.begin(); i != symbolDatabase->spaceInfoList.end(); ++i)
    {
        const SymbolDatabase::SpaceInfo *info = *i;


        if (info->isClassOrStruct())
        {
            std::list<SymbolDatabase::Func>::const_iterator func;

            for (func = info->functionList.begin(); func != info->functionList.end(); ++func)
            {
                if (func->type == SymbolDatabase::Func::OperatorEqual && func->hasBody)
                {

                    if (Token::Match(func->tokenDef->tokAt(-4), ";|}|{|public:|protected:|private: %type% &") &&
                        func->tokenDef->strAt(-3) == info->className)
                    {

                        const Token *tok = func->token->next()->link();

                        checkReturnPtrThis(info, &(*func), tok->tokAt(2), tok->next()->link());
                    }
                }
            }
        }
    }
}
