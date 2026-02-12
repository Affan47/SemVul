void Parser::ParseStmtList(ParseNodePtr *ppnodeList, ParseNodePtr **pppnodeLast, StrictModeEnvironment smEnvironment, const bool isSourceElementList, bool* strictModeOn)
{
    BOOL doneDirectives = !isSourceElementList;
    BOOL seenDirectiveContainingOctal = false;

    BOOL old_UseStrictMode = m_fUseStrictMode;

    ParseNodePtr pnodeStmt;
    ParseNodePtr *lastNodeRef = nullptr;

    if (buildAST)
    {
        AssertMem(ppnodeList);
        AssertMemN(pppnodeLast);
        *ppnodeList = nullptr;
    }

    if(CONFIG_FLAG(ForceStrictMode))
    {
        m_fUseStrictMode = TRUE;
    }

    for (;;)
    {
        switch (m_token.tk)
        {
        case tkCASE:
        case tkDEFAULT:
        case tkRCurly:
        case tkEOF:
            if (buildAST && nullptr != pppnodeLast)
            {
                *pppnodeLast = lastNodeRef;
            }
            if (!buildAST)
            {
                m_fUseStrictMode = old_UseStrictMode;
            }
            return;
        }

        if (doneDirectives == FALSE)
        {
            bool isOctalInString = false;
            bool isUseStrictDirective = false;
            bool isUseAsmDirective = false;
            if (smEnvironment != SM_NotUsed && CheckForDirective(&isUseStrictDirective, &isUseAsmDirective, &isOctalInString))
            {

                isUseAsmDirective &= buildAST;

                if (isUseStrictDirective)
                {

                    if (GetCurrentFunctionNode()->sxFnc.HasNonSimpleParameterList())
                    {
                        Error(ERRNonSimpleParamListInStrictMode);
                    }

                    if (seenDirectiveContainingOctal)
                    {

                        Error(ERRES5NoOctal);
                    }
                    if (!buildAST)
                    {

                        m_fUseStrictMode = TRUE;
                        if (!m_inDeferredNestedFunc)
                        {

                            Assert(m_currentNodeFunc != nullptr);
                            m_currentNodeFunc->sxFnc.SetStrictMode();
                        }
                        else if (strictModeOn)
                        {


                            *strictModeOn = true;
                        }
                    }
                    else
                    {
                        if (smEnvironment == SM_OnGlobalCode)
                        {

                            m_fUseStrictMode = TRUE;
                        }
                        else
                        {

                            Assert(m_currentNodeFunc != nullptr);
                            m_currentNodeFunc->sxFnc.SetStrictMode();
                        }
                    }
                }
                else if (isUseAsmDirective)
                {
                    if (smEnvironment != SM_OnGlobalCode)
                    {

                        Assert(m_currentNodeFunc != nullptr);
                        m_currentNodeFunc->sxFnc.SetAsmjsMode();
                        m_currentNodeFunc->sxFnc.SetCanBeDeferred(false);
                        m_InAsmMode = true;

                        CHAKRATEL_LANGSTATS_INC_LANGFEATURECOUNT(AsmJSFunction, m_scriptContext);
                    }
                }
                else if (isOctalInString)
                {
                    seenDirectiveContainingOctal = TRUE;
                }
            }
            else
            {

                doneDirectives = TRUE;
            }
        }

        if (nullptr != (pnodeStmt = ParseStatement<buildAST>()))
        {
            if (buildAST)
            {
                AddToNodeList(ppnodeList, &lastNodeRef, pnodeStmt);
            }
        }
    }
}
