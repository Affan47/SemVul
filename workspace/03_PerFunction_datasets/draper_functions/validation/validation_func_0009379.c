checkSuspiciousSemicolon()
{
    if (!_settings->inconclusive || !_settings->isEnabled("style"))
        return;

    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();


    for (std::list<Scope>::const_iterator i = symbolDatabase->scopeList.begin(); i != symbolDatabase->scopeList.end(); ++i) {
        if (i->type == Scope::eIf || i->type == Scope::eElse || i->type == Scope::eElseIf || i->type == Scope::eWhile || i->type == Scope::eFor) {


            if (Token::simpleMatch(i->classStart, "{ ; } {") &&
                i->classStart->previous()->linenr() == i->classStart->tokAt(2)->linenr()
                && i->classStart->linenr()+1 >= i->classStart->tokAt(3)->linenr()) {
                SuspiciousSemicolonError(i->classStart);
            }
        }
    }
}
