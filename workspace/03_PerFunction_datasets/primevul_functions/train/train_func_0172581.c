void Parser::PushFuncBlockScope(ParseNodePtr pnodeBlock, ParseNodePtr **ppnodeScopeSave, ParseNodePtr **ppnodeExprScopeSave)
{


    pnodeBlock->sxBlock.pnodeScopes = nullptr;
    pnodeBlock->sxBlock.pnodeNext = nullptr;


    if (m_ppnodeExprScope)
    {
        *ppnodeScopeSave = m_ppnodeScope;

        Assert(*m_ppnodeExprScope == nullptr);
        *m_ppnodeExprScope = pnodeBlock;
        *ppnodeExprScopeSave = &pnodeBlock->sxBlock.pnodeNext;
    }
    else
    {
        Assert(m_ppnodeScope);
        Assert(*m_ppnodeScope == nullptr);
        *m_ppnodeScope = pnodeBlock;
        *ppnodeScopeSave = &pnodeBlock->sxBlock.pnodeNext;

        *ppnodeExprScopeSave = m_ppnodeExprScope;
    }


    m_ppnodeScope = &pnodeBlock->sxBlock.pnodeScopes;

    m_ppnodeExprScope = nullptr;
}
