void Parser::FinishFncNode(ParseNodePtr pnodeFnc)
{
    AnalysisAssert(pnodeFnc);


    Js::LocalFunctionId * nextFunctionIdSave = m_nextFunctionId;
    Js::LocalFunctionId tempNextFunctionId = pnodeFnc->sxFnc.functionId + 1;
    this->m_nextFunctionId = &tempNextFunctionId;

    ParseNodePtr pnodeFncSave = m_currentNodeFunc;
    uint *pnestedCountSave = m_pnestedCount;
    int32* pAstSizeSave = m_pCurrentAstSize;

    m_currentNodeFunc = pnodeFnc;
    m_pCurrentAstSize = & (pnodeFnc->sxFnc.astSize);

    pnodeFnc->sxFnc.nestedCount = 0;
    m_pnestedCount = &pnodeFnc->sxFnc.nestedCount;


    if (pnodeFnc->sxFnc.pnodeName)
    {

        m_pscan->SetCurrentCharacter(pnodeFnc->sxFnc.pnodeName->ichLim, pnodeFnc->sxFnc.lineNumber);
    }
    else
    {
        m_pscan->SetCurrentCharacter(pnodeFnc->ichMin, pnodeFnc->sxFnc.lineNumber);
        if (pnodeFnc->sxFnc.IsAccessor())
        {

            m_pscan->ScanNoKeywords();
        }
        else
        {

            for (;;)
            {
                m_pscan->Scan();
                if (m_token.GetIdentifier(m_phtbl) == wellKnownPropertyPids.async)
                {
                    Assert(pnodeFnc->sxFnc.IsAsync());
                    continue;
                }
                if (m_token.tk == tkFUNCTION)
                {
                    break;
                }
                Assert(m_token.tk == tkLParen || m_token.tk == tkStar);
            }
        }
    }


    bool fPreviousYieldIsKeyword = m_pscan->SetYieldIsKeyword(pnodeFnc && pnodeFnc->sxFnc.IsGenerator());

    bool fPreviousAwaitIsKeyword = m_pscan->SetAwaitIsKeyword(pnodeFnc && pnodeFnc->sxFnc.IsAsync());


    m_pscan->ScanNoKeywords();
    if (m_token.tk == tkStar)
    {
        Assert(pnodeFnc->sxFnc.IsGenerator());
        m_pscan->ScanNoKeywords();
    }
    Assert(m_token.tk == tkLParen);
    m_pscan->ScanNoKeywords();

    if (m_token.tk != tkRParen)
    {
        for (;;)
        {
            if (m_token.tk == tkEllipsis)
            {
                m_pscan->ScanNoKeywords();
            }

            if (m_token.tk == tkID)
            {
                m_pscan->ScanNoKeywords();

                if (m_token.tk == tkAsg)
                {

                    m_pscan->Scan();
                    ParseExpr<false>(koplCma);
                }
            }
            else if (IsPossiblePatternStart())
            {
                ParseDestructuredLiteralWithScopeSave(tkLET, false, false );
            }
            else
            {
                AssertMsg(false, "Unexpected identifier prefix while fast-scanning formals");
            }

            if (m_token.tk != tkComma)
            {
                break;
            }
            m_pscan->ScanNoKeywords();

            if (m_token.tk == tkRParen && m_scriptContext->GetConfig()->IsES7TrailingCommaEnabled())
            {
                break;
            }
        }
    }

    if (m_token.tk == tkRParen)
    {
        m_pscan->Scan();
    }


    {


        ParseNodePtr* lastNodeRef = NULL;
        const charcount_t ichLim = pnodeFnc->ichLim;
        const size_t cbLim = pnodeFnc->sxFnc.cbLim;
        this->FinishFncDecl(pnodeFnc, NULL, lastNodeRef);

#if DBG


        if (pnodeFnc->ichLim != ichLim)
        {
            Assert(pnodeFnc->ichLim < ichLim);
            m_pscan->SetCurrentCharacter(pnodeFnc->ichLim);
            while (m_pscan->IchLimTok() != ichLim)
            {
                m_pscan->ScanNoKeywords();
                Assert(m_token.tk == tkRParen);
            }
        }
#endif
        pnodeFnc->ichLim = ichLim;
        pnodeFnc->sxFnc.cbLim = cbLim;
    }

    m_currentNodeFunc = pnodeFncSave;
    m_pCurrentAstSize = pAstSizeSave;
    m_pnestedCount = pnestedCountSave;
    Assert(m_pnestedCount);

    Assert(tempNextFunctionId == pnodeFnc->sxFnc.deferredParseNextFunctionId);
    this->m_nextFunctionId = nextFunctionIdSave;

    m_pscan->SetYieldIsKeyword(fPreviousYieldIsKeyword);
    m_pscan->SetAwaitIsKeyword(fPreviousAwaitIsKeyword);
}
