void Parser::ParseFncFormals(ParseNodePtr pnodeFnc, ParseNodePtr pnodeParentFnc, ushort flags)
{
    bool fLambda = (flags & fFncLambda) != 0;
    bool fMethod = (flags & fFncMethod) != 0;
    bool fNoArg = (flags & fFncNoArg) != 0;
    bool fOneArg = (flags & fFncOneArg) != 0;
    bool fAsync = (flags & fFncAsync) != 0;

    bool fPreviousYieldIsKeyword = false;
    bool fPreviousAwaitIsKeyword = false;

    if (fLambda)
    {
        fPreviousYieldIsKeyword = m_pscan->SetYieldIsKeyword(pnodeParentFnc != nullptr && pnodeParentFnc->sxFnc.IsGenerator());
        fPreviousAwaitIsKeyword = m_pscan->SetAwaitIsKeyword(fAsync || (pnodeParentFnc != nullptr && pnodeParentFnc->sxFnc.IsAsync()));
    }

    Assert(!fNoArg || !fOneArg);


    bool fStrictFormals = IsStrictMode() || fLambda || fMethod;


    bool forcePid = fStrictFormals && !fNoArg && !fOneArg;
    AutoTempForcePid autoForcePid(m_pscan, forcePid);


    if (fLambda && m_token.tk == tkID)
    {
        IdentPtr pid = m_token.GetIdentifier(m_phtbl);

        CreateVarDeclNode(pid, STFormal, false, nullptr, false);
        CheckPidIsValid(pid);

        m_pscan->Scan();

        if (m_token.tk != tkDArrow)
        {
            Error(ERRsyntax, m_pscan->IchMinTok(), m_pscan->IchLimTok());
        }

        if (fLambda)
        {
            m_pscan->SetYieldIsKeyword(fPreviousYieldIsKeyword);
            m_pscan->SetAwaitIsKeyword(fPreviousAwaitIsKeyword);
        }

        return;
    }
    else if (fLambda && m_token.tk == tkAWAIT)
    {

        IdentifierExpectedError(m_token);
    }


    ChkCurTok(tkLParen, ERRnoLparen);


    if (m_token.tk == tkRParen)
    {
        if (fOneArg)
        {
            Error(ERRSetterMustHaveOneParameter);
        }
    }
    else
    {
        if (fNoArg)
        {
            Error(ERRGetterMustHaveNoParameters);
        }
        SList<IdentPtr> formals(&m_nodeAllocator);
        ParseNodePtr pnodeT = nullptr;
        bool seenRestParameter = false;
        bool isNonSimpleParameterList = false;
        for (Js::ArgSlot argPos = 0; ; ++argPos)
        {
            bool isBindingPattern = false;
            if (m_scriptContext->GetConfig()->IsES6RestEnabled() && m_token.tk == tkEllipsis)
            {

                m_pscan->Scan();
                seenRestParameter = true;
            }
            if (m_token.tk != tkID)
            {
                if (IsES6DestructuringEnabled() && IsPossiblePatternStart())
                {

                    this->GetCurrentFunctionNode()->sxFnc.SetHasNonSimpleParameterList();

                    ParseNodePtr *const ppnodeVarSave = m_ppnodeVar;
                    m_ppnodeVar = &pnodeFnc->sxFnc.pnodeVars;

                    ParseNodePtr * ppNodeLex = m_currentBlockInfo->m_ppnodeLex;
                    Assert(ppNodeLex != nullptr);

                    ParseNodePtr paramPattern = nullptr;
                    ParseNodePtr pnodePattern = ParseDestructuredLiteral<buildAST>(tkLET, true , false );


                    for (ParseNodePtr lexNode = *ppNodeLex; lexNode != nullptr; lexNode = lexNode->sxVar.pnodeNext)
                    {
                        Assert(lexNode->IsVarLetOrConst());
                        UpdateOrCheckForDuplicateInFormals(lexNode->sxVar.pid, &formals);
                        lexNode->sxVar.sym->SetSymbolType(STFormal);
                        if (m_currentNodeFunc != nullptr && lexNode->sxVar.pid == wellKnownPropertyPids.arguments)
                        {
                            m_currentNodeFunc->grfpn |= PNodeFlags::fpnArguments_overriddenByDecl;
                        }
                    }

                    m_ppnodeVar = ppnodeVarSave;
                    if (buildAST)
                    {
                        paramPattern = CreateParamPatternNode(pnodePattern);


                        *m_ppnodeVar = paramPattern;
                        paramPattern->sxParamPattern.pnodeNext = nullptr;
                        m_ppnodeVar = &paramPattern->sxParamPattern.pnodeNext;
                    }

                    isBindingPattern = true;
                    isNonSimpleParameterList = true;
                }
                else
                {
                    IdentifierExpectedError(m_token);
                }
            }

            if (!isBindingPattern)
            {
                IdentPtr pid = m_token.GetIdentifier(m_phtbl);
                LPCOLESTR pNameHint = pid->Psz();
                uint32 nameHintLength = pid->Cch();
                uint32 nameHintOffset = 0;

                if (seenRestParameter)
                {
                    this->GetCurrentFunctionNode()->sxFnc.SetHasNonSimpleParameterList();
                    if (flags & fFncOneArg)
                    {

                        Error(ERRUnexpectedEllipsis);
                    }
                    pnodeT = CreateDeclNode(knopVarDecl, pid, STFormal, false);
                    pnodeT->sxVar.sym->SetIsNonSimpleParameter(true);
                    if (buildAST)
                    {

                        pnodeFnc->sxFnc.pnodeRest = pnodeT;
                        if (!isNonSimpleParameterList)
                        {


                            MapFormalsWithoutRest(m_currentNodeFunc, [&](ParseNodePtr pnodeArg) { pnodeArg->sxVar.sym->SetIsNonSimpleParameter(true); });
                        }
                    }

                    isNonSimpleParameterList = true;
                }
                else
                {
                    pnodeT = CreateVarDeclNode(pid, STFormal, false, nullptr, false);
                    if (isNonSimpleParameterList)
                    {
                        pnodeT->sxVar.sym->SetIsNonSimpleParameter(true);
                    }
                }

                if (buildAST && pid == wellKnownPropertyPids.arguments)
                {

                    m_currentNodeFunc->grfpn |= PNodeFlags::fpnArguments_overriddenByDecl;
                }

                if (fStrictFormals)
                {
                    UpdateOrCheckForDuplicateInFormals(pid, &formals);
                }

                m_pscan->Scan();

                if (seenRestParameter && m_token.tk != tkRParen && m_token.tk != tkAsg)
                {
                    Error(ERRRestLastArg);
                }

                if (m_token.tk == tkAsg && m_scriptContext->GetConfig()->IsES6DefaultArgsEnabled())
                {
                    if (seenRestParameter && m_scriptContext->GetConfig()->IsES6RestEnabled())
                    {
                        Error(ERRRestWithDefault);
                    }


                    ParseNode* currentFncNode = GetCurrentFunctionNode();
                    if (!currentFncNode->sxFnc.HasDefaultArguments())
                    {
                        currentFncNode->sxFnc.SetHasDefaultArguments();
                        currentFncNode->sxFnc.SetHasNonSimpleParameterList();
                        currentFncNode->sxFnc.firstDefaultArg = argPos;
                    }

                    m_pscan->Scan();
                    ParseNodePtr pnodeInit = ParseExpr<buildAST>(koplCma, nullptr, TRUE, FALSE, pNameHint, &nameHintLength, &nameHintOffset);

                    if (buildAST && pnodeInit->nop == knopFncDecl)
                    {
                        Assert(nameHintLength >= nameHintOffset);
                        pnodeInit->sxFnc.hint = pNameHint;
                        pnodeInit->sxFnc.hintLength = nameHintLength;
                        pnodeInit->sxFnc.hintOffset = nameHintOffset;
                    }

                    AnalysisAssert(pnodeT);
                    pnodeT->sxVar.sym->SetIsNonSimpleParameter(true);
                    if (!isNonSimpleParameterList)
                    {
                        if (buildAST)
                        {


                            MapFormalsWithoutRest(m_currentNodeFunc, [&](ParseNodePtr pnodeArg) { pnodeArg->sxVar.sym->SetIsNonSimpleParameter(true); });
                        }


                        isNonSimpleParameterList = true;
                    }

                    if (buildAST)
                    {
                        if (!m_currentNodeFunc->sxFnc.HasDefaultArguments())
                        {
                            CHAKRATEL_LANGSTATS_INC_LANGFEATURECOUNT(DefaultArgFunction, m_scriptContext);
                        }
                        pnodeT->sxVar.pnodeInit = pnodeInit;
                        pnodeT->ichLim = m_pscan->IchLimTok();
                    }
                }
            }

            if (isNonSimpleParameterList && m_currentScope->GetHasDuplicateFormals())
            {
                Error(ERRFormalSame);
            }

            if (flags & fFncOneArg)
            {
                if (m_token.tk != tkRParen)
                {
                    Error(ERRSetterMustHaveOneParameter);
                }
                break;
            }

            if (m_token.tk != tkComma)
            {
                break;
            }

            m_pscan->Scan();

            if (m_token.tk == tkRParen && m_scriptContext->GetConfig()->IsES7TrailingCommaEnabled())
            {
                break;
            }
        }

        if (seenRestParameter)
        {
            CHAKRATEL_LANGSTATS_INC_LANGFEATURECOUNT(Rest, m_scriptContext);
        }

        if (m_token.tk != tkRParen)
        {
            Error(ERRnoRparen);
        }

        if (this->GetCurrentFunctionNode()->sxFnc.CallsEval() || this->GetCurrentFunctionNode()->sxFnc.ChildCallsEval())
        {
            if (!m_scriptContext->GetConfig()->IsES6DefaultArgsSplitScopeEnabled())
            {
                Error(ERREvalNotSupportedInParamScope);
            }
            else
            {
                Assert(pnodeFnc->sxFnc.HasNonSimpleParameterList());
                pnodeFnc->sxFnc.pnodeScopes->sxBlock.scope->SetCannotMergeWithBodyScope();
            }
        }
    }
    Assert(m_token.tk == tkRParen);

    if (fLambda)
    {
        m_pscan->SetYieldIsKeyword(fPreviousYieldIsKeyword);
        m_pscan->SetAwaitIsKeyword(fPreviousAwaitIsKeyword);
    }
}
