ParseNodePtr Parser::ParseDestructuredInitializer(ParseNodePtr lhsNode,
    bool isDecl,
    bool topLevel,
    DestructuringInitializerContext initializerContext,
    bool allowIn,
    BOOL *forInOfOkay,
    BOOL *nativeForOkay)
{
    m_pscan->Scan();
    if (topLevel && nativeForOkay == nullptr)
    {
        if (initializerContext != DIC_ForceErrorOnInitializer && m_token.tk != tkAsg)
        {

            Error(ERRDestructInit);
        }
        else if (initializerContext == DIC_ForceErrorOnInitializer && m_token.tk == tkAsg)
        {

            Error(ERRDestructNotInit);
        }
    }

    if (m_token.tk != tkAsg || initializerContext == DIC_ShouldNotParseInitializer)
    {
        if (topLevel && nativeForOkay != nullptr)
        {

            *nativeForOkay = FALSE;
        }

        return lhsNode;
    }

    if (forInOfOkay)
    {
        *forInOfOkay = FALSE;
    }

    m_pscan->Scan();


    bool alreadyHasInitError = m_hasDeferredShorthandInitError;

    ParseNodePtr pnodeDefault = ParseExpr<buildAST>(koplCma, nullptr, allowIn);

    if (m_hasDeferredShorthandInitError && !alreadyHasInitError)
    {
        Error(ERRnoColon);
    }

    ParseNodePtr pnodeDestructAsg = nullptr;
    if (buildAST)
    {
        Assert(lhsNode != nullptr);

        pnodeDestructAsg = CreateNodeWithScanner<knopAsg>();
        pnodeDestructAsg->sxBin.pnode1 = lhsNode;
        pnodeDestructAsg->sxBin.pnode2 = pnodeDefault;
        pnodeDestructAsg->ichMin = lhsNode->ichMin;
        pnodeDestructAsg->ichLim = pnodeDefault->ichLim;
    }
    return pnodeDestructAsg;
}
