ParseNodePtr Parser::ParseDestructuredLiteral(tokens declarationType,
    bool isDecl,
    bool topLevel,
    DestructuringInitializerContext initializerContext,
    bool allowIn,
    BOOL *forInOfOkay,
    BOOL *nativeForOkay)
{
    ParseNodePtr pnode = nullptr;
    Assert(IsPossiblePatternStart());
    if (m_token.tk == tkLCurly)
    {
        pnode = ParseDestructuredObjectLiteral<buildAST>(declarationType, isDecl, topLevel);
    }
    else
    {
        pnode = ParseDestructuredArrayLiteral<buildAST>(declarationType, isDecl, topLevel);
    }

    return ParseDestructuredInitializer<buildAST>(pnode, isDecl, topLevel, initializerContext, allowIn, forInOfOkay, nativeForOkay);
}
