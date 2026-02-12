HRESULT Parser::ParseFunctionInBackground(ParseNodePtr pnodeFnc, ParseContext *parseContext, bool topLevelDeferred, CompileScriptException *pse)
{
    m_functionBody = nullptr;
    m_parseType = ParseType_Upfront;
    HRESULT hr = S_OK;
    SmartFPUControl smartFpuControl;
    uint nextFunctionId = pnodeFnc->sxFnc.functionId + 1;

    this->RestoreContext(parseContext);
    DebugOnly( m_err.fInited = TRUE; )
    m_nextFunctionId = &nextFunctionId;
    m_deferringAST = topLevelDeferred;
    m_inDeferredNestedFunc = false;
    m_scopeCountNoAst = 0;

    SetCurrentStatement(nullptr);

    pnodeFnc->sxFnc.pnodeVars = nullptr;
    pnodeFnc->sxFnc.pnodeParams = nullptr;
    pnodeFnc->sxFnc.pnodeBody = nullptr;
    pnodeFnc->sxFnc.nestedCount = 0;

    ParseNodePtr pnodeParentFnc = GetCurrentFunctionNode();
    m_currentNodeFunc = pnodeFnc;
    m_currentNodeDeferredFunc = nullptr;
    m_ppnodeScope = nullptr;
    m_ppnodeExprScope = nullptr;

    m_pnestedCount = &pnodeFnc->sxFnc.nestedCount;
    m_pCurrentAstSize = &pnodeFnc->sxFnc.astSize;

    ParseNodePtr pnodeBlock = StartParseBlock<true>(PnodeBlockType::Function, ScopeType_FunctionBody);
    pnodeFnc->sxFnc.pnodeScopes = pnodeBlock;
    m_ppnodeScope = &pnodeBlock->sxBlock.pnodeScopes;

    uint uDeferSave = m_grfscr & fscrDeferFncParse;

    try
    {
        m_pscan->Scan();

        m_ppnodeVar = &pnodeFnc->sxFnc.pnodeParams;
        this->ParseFncFormals<true>(pnodeFnc, pnodeParentFnc, fFncNoFlgs);

        if (m_token.tk == tkRParen)
        {
            m_pscan->Scan();
        }

        ChkCurTok(tkLCurly, ERRnoLcurly);

        m_ppnodeVar = &pnodeFnc->sxFnc.pnodeVars;


        BYTE deferFlags = m_pscan->SetDeferredParse(topLevelDeferred);


        if (topLevelDeferred)
        {
            ParseStmtList<false>(nullptr, nullptr, SM_DeferredParse, true);
        }
        else
        {
            ParseNodePtr *lastNodeRef = nullptr;
            ParseStmtList<true>(&pnodeFnc->sxFnc.pnodeBody, &lastNodeRef, SM_OnFunctionCode, true);
            AddArgumentsNodeToVars(pnodeFnc);

            AddToNodeList(&pnodeFnc->sxFnc.pnodeBody, &lastNodeRef, CreateNodeWithScanner<knopEndCode>());
        }


        m_pscan->SetDeferredParseFlags(deferFlags);

#if DBG
        pnodeFnc->sxFnc.deferredParseNextFunctionId = *this->m_nextFunctionId;
#endif
        this->m_deferringAST = FALSE;


        FinishParseBlock(pnodeBlock);
    }
    catch(ParseExceptionObject& e)
    {
        m_err.m_hr = e.GetError();
        hr = pse->ProcessError( m_pscan, m_err.m_hr, nullptr);
    }

    if (IsStrictMode())
    {
        pnodeFnc->sxFnc.SetStrictMode();
    }

    if (topLevelDeferred)
    {
        pnodeFnc->sxFnc.pnodeVars = nullptr;
    }

    m_grfscr |= uDeferSave;

    Assert(nullptr == *m_ppnodeScope);

    return hr;
}
