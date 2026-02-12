void Parser::UpdateCurrentNodeFunc(ParseNodePtr pnodeFnc, bool fLambda)
{
    if (buildAST)
    {

        m_currentNodeFunc = pnodeFnc;

        Assert(m_currentNodeDeferredFunc == nullptr);

        if (!fLambda)
        {
            m_currentNodeNonLambdaFunc = pnodeFnc;
        }
    }
    else
    {
        AnalysisAssert(pnodeFnc);

        if (!fLambda)
        {
            m_currentNodeNonLambdaDeferredFunc = pnodeFnc;
        }

        m_currentNodeDeferredFunc = pnodeFnc;
    }
}
