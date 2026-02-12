void Parser::ParseNestedDeferredFunc(ParseNodePtr pnodeFnc, bool fLambda, bool *pNeedScanRCurly, bool *pStrictModeTurnedOn)
{


    size_t lengthBeforeBody = this->GetSourceLength();

    if (m_token.tk != tkLCurly && fLambda)
    {
        ParseExpressionLambdaBody<false>(pnodeFnc);
        *pNeedScanRCurly = false;
    }
    else
    {
        ChkCurTok(tkLCurly, ERRnoLcurly);

        bool* detectStrictModeOn = IsStrictMode() ? nullptr : pStrictModeTurnedOn;
        m_ppnodeVar = &m_currentNodeDeferredFunc->sxFnc.pnodeVars;

        ParseStmtList<false>(nullptr, nullptr, SM_DeferredParse, true , detectStrictModeOn);

        ChkCurTokNoScan(tkRCurly, ERRnoRcurly);
    }

    pnodeFnc->ichLim = m_pscan->IchLimTok();
    pnodeFnc->sxFnc.cbLim = m_pscan->IecpLimTok();
    if (*pStrictModeTurnedOn)
    {
        pnodeFnc->sxFnc.SetStrictMode(true);
    }

    if (!PHASE_OFF1(Js::SkipNestedDeferredPhase))
    {


        RestorePoint *restorePoint = Anew(&m_nodeAllocator, RestorePoint);
        m_pscan->Capture(restorePoint,
                         *m_nextFunctionId - pnodeFnc->sxFnc.functionId - 1,
                         lengthBeforeBody - this->GetSourceLength());
        pnodeFnc->sxFnc.pRestorePoint = restorePoint;
    }
}
