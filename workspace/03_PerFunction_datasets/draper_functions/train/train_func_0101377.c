stlBoundaries()
{
    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {

            if (tok->str() == "<" && Token::Match(tok->previous(), "bitset|list|forward_list|map|multimap|multiset|priority_queue|queue|set|stack|hash_map|hash_multimap|hash_set|unordered_map|unordered_multimap|unordered_set|unordered_multiset")) {
                if (!tok->link())
                    continue;
                const std::string& container_name(tok->strAt(-1));
                tok = tok->link();

                if (Token::Match(tok, "> :: iterator|const_iterator %var% =|;")) {
                    const unsigned int iteratorid(tok->tokAt(3)->varId());
                    if (iteratorid == 0)
                        continue;


                    const Token* const end = tok->scope()->classEnd;
                    for (const Token *tok2 = tok; tok2 != end; tok2 = tok2->next()) {
                        if (Token::Match(tok2, "!!* %varid% <", iteratorid)) {
                            stlBoundariesError(tok2, container_name);
                        } else if (Token::Match(tok2, "> %varid% !!.", iteratorid)) {
                            stlBoundariesError(tok2, container_name);
                        }
                    }
                }
            }
        }
    }
}
