ParseNodePtr Parser::Parse(LPCUTF8 pszSrc, size_t offset, size_t length, charcount_t charOffset, ULONG grfscr, ULONG lineNumber, Js::LocalFunctionId * nextFunctionId, CompileScriptException *pse)
{
    ParseNodePtr pnodeProg;
    ParseNodePtr *lastNodeRef = nullptr;

    m_nextBlockId = 0;


    grfscr &= ~fscrSyntaxColor;

    if (this->m_scriptContext->IsScriptContextInDebugMode()
#ifdef ENABLE_PREJIT
         || Js::Configuration::Global.flags.Prejit
#endif
         || ((grfscr & fscrNoDeferParse) != 0)
        )
    {


        grfscr &= ~fscrDeferFncParse;
    }
    else if (!(grfscr & fscrGlobalCode) &&
             (
                 PHASE_OFF1(Js::Phase::DeferEventHandlersPhase) ||
                 this->m_scriptContext->IsScriptContextInSourceRundownOrDebugMode()
             )
        )
    {


        grfscr &= ~fscrDeferFncParse;
    }

    bool isDeferred = (grfscr & fscrDeferredFnc) != 0;
    bool isModuleSource = (grfscr & fscrIsModuleCode) != 0;

    m_grfscr = grfscr;
    m_length = length;
    m_originalLength = length;
    m_nextFunctionId = nextFunctionId;

    if(m_parseType != ParseType_Deferred)
    {
        JS_ETW(EventWriteJSCRIPT_PARSE_METHOD_START(m_sourceContextInfo->dwHostSourceContext, GetScriptContext(), *m_nextFunctionId, 0, m_parseType, Js::Constants::GlobalFunction));
        OUTPUT_TRACE(Js::DeferParsePhase, _u("Parsing function (%s) : %s (%d)\n"), GetParseType(), Js::Constants::GlobalFunction, *m_nextFunctionId);
    }


    m_pscan->SetText(pszSrc, offset, length, charOffset, grfscr, lineNumber);
    m_pscan->Scan();


    int32 initSize = 0;
    m_pCurrentAstSize = &initSize;
    pnodeProg = CreateProgNodeWithScanner(isModuleSource);
    pnodeProg->grfpn = PNodeFlags::fpnNone;
    pnodeProg->sxFnc.pid = nullptr;
    pnodeProg->sxFnc.pnodeName = nullptr;
    pnodeProg->sxFnc.pnodeRest = nullptr;
    pnodeProg->sxFnc.ClearFlags();
    pnodeProg->sxFnc.SetNested(FALSE);
    pnodeProg->sxFnc.astSize = 0;
    pnodeProg->sxFnc.cbMin = m_pscan->IecpMinTok();
    pnodeProg->sxFnc.lineNumber = lineNumber;
    pnodeProg->sxFnc.columnNumber = 0;

    if (!isDeferred || (isDeferred && grfscr & fscrGlobalCode))
    {


        pnodeProg->sxFnc.functionId = (*m_nextFunctionId)++;
    }
    else
    {
        pnodeProg->sxFnc.functionId = Js::Constants::NoFunctionId;
    }

    if (isModuleSource)
    {
        Assert(m_scriptContext->GetConfig()->IsES6ModuleEnabled());

        pnodeProg->sxModule.localExportEntries = nullptr;
        pnodeProg->sxModule.indirectExportEntries = nullptr;
        pnodeProg->sxModule.starExportEntries = nullptr;
        pnodeProg->sxModule.importEntries = nullptr;
        pnodeProg->sxModule.requestedModules = nullptr;
    }

    m_pCurrentAstSize = & (pnodeProg->sxFnc.astSize);

    pnodeProg->sxFnc.hint = nullptr;
    pnodeProg->sxFnc.hintLength = 0;
    pnodeProg->sxFnc.hintOffset = 0;
    pnodeProg->sxFnc.isNameIdentifierRef = true;
    pnodeProg->sxFnc.nestedFuncEscapes = false;


    pnodeProg->sxFnc.pnodeNext = nullptr;

    m_currentNodeFunc = nullptr;
    m_currentNodeDeferredFunc = nullptr;
    m_currentNodeProg = pnodeProg;
    m_cactIdentToNodeLookup = 1;

    pnodeProg->sxFnc.nestedCount = 0;
    m_pnestedCount = &pnodeProg->sxFnc.nestedCount;
    m_inDeferredNestedFunc = false;

    pnodeProg->sxFnc.pnodeParams = nullptr;
    pnodeProg->sxFnc.pnodeVars = nullptr;
    pnodeProg->sxFnc.pnodeRest = nullptr;
    m_ppnodeVar = &pnodeProg->sxFnc.pnodeVars;
    SetCurrentStatement(nullptr);
    AssertMsg(m_pstmtCur == nullptr, "Statement stack should be empty when we start parse global code");


    ParseNodePtr pnodeGlobalBlock = StartParseBlock<true>(PnodeBlockType::Global, ScopeType_Global);
    pnodeProg->sxProg.scope = pnodeGlobalBlock->sxBlock.scope;
    ParseNodePtr pnodeGlobalEvalBlock = nullptr;


    m_ppnodeExprScope = nullptr;


    pnodeProg->sxFnc.pnodeBodyScope = nullptr;
    pnodeProg->sxFnc.pnodeScopes = pnodeGlobalBlock;
    m_ppnodeScope = &pnodeGlobalBlock->sxBlock.pnodeScopes;

    if ((this->m_grfscr & fscrEvalCode) &&
        !(this->m_functionBody && this->m_functionBody->GetScopeInfo()))
    {
        pnodeGlobalEvalBlock = StartParseBlock<true>(PnodeBlockType::Regular, ScopeType_GlobalEvalBlock);
        pnodeProg->sxFnc.pnodeScopes = pnodeGlobalEvalBlock;
        m_ppnodeScope = &pnodeGlobalEvalBlock->sxBlock.pnodeScopes;
    }

    Js::ScopeInfo *scopeInfo = nullptr;
    if (m_parseType == ParseType_Deferred && m_functionBody)
    {

        scopeInfo = m_functionBody->GetScopeInfo();
        if (scopeInfo)
        {

            m_currentNodeFunc = CreateNode(knopFncDecl);
            m_currentNodeFunc->sxFnc.pnodeName = nullptr;
            m_currentNodeFunc->sxFnc.functionId = m_functionBody->GetLocalFunctionId();
            m_currentNodeFunc->sxFnc.nestedCount = m_functionBody->GetNestedCount();
            m_currentNodeFunc->sxFnc.SetStrictMode(!!this->m_fUseStrictMode);

            this->RestoreScopeInfo(scopeInfo->GetParent());
        }
    }


    if (isModuleSource && (!isDeferred || (isDeferred && grfscr & fscrGlobalCode)))
    {
        ParseNodePtr moduleFunction = GenerateModuleFunctionWrapper<true>();
        pnodeProg->sxFnc.pnodeBody = nullptr;
        AddToNodeList(&pnodeProg->sxFnc.pnodeBody, &lastNodeRef, moduleFunction);
    }
    else
    {

        ParseStmtList<true>(
            &pnodeProg->sxFnc.pnodeBody,
            &lastNodeRef,
            SM_OnGlobalCode,
            !(m_grfscr & fscrDeferredFncExpression) );
    }

    if (m_parseType == ParseType_Deferred)
    {
        if (scopeInfo)
        {
            this->FinishScopeInfo(scopeInfo->GetParent());
        }
    }

    pnodeProg->sxProg.m_UsesArgumentsAtGlobal = m_UsesArgumentsAtGlobal;

    if (IsStrictMode())
    {
        pnodeProg->sxFnc.SetStrictMode();
    }

#if DEBUG
    if(m_grfscr & fscrEnforceJSON && !IsJSONValid(pnodeProg->sxFnc.pnodeBody))
    {
        Error(ERRsyntax);
    }
#endif

    if (tkEOF != m_token.tk)
        Error(ERRsyntax);


    AddToNodeList(&pnodeProg->sxFnc.pnodeBody, &lastNodeRef,
        CreateNodeWithScanner<knopEndCode>());
    AssertMem(lastNodeRef);
    AssertNodeMem(*lastNodeRef);
    Assert((*lastNodeRef)->nop == knopEndCode);
    (*lastNodeRef)->ichMin = 0;
    (*lastNodeRef)->ichLim = 0;


    pnodeProg->ichLim = m_pscan->IchLimTok();
    pnodeProg->sxFnc.cbLim = m_pscan->IecpLimTok();


    *m_ppnodeVar = nullptr;

    Assert(nullptr == *m_ppnodeScope);
    Assert(nullptr == pnodeProg->sxFnc.pnodeNext);

#ifdef ENABLE_DEBUG_CONFIG_OPTIONS
    if (Js::Configuration::Global.flags.IsEnabled(Js::ForceUndoDeferFlag))
    {
        m_stoppedDeferredParse = true;
    }
#endif

    if (m_stoppedDeferredParse)
    {
        if (this->m_hasParallelJob)
        {
#if ENABLE_BACKGROUND_PARSING
            BackgroundParser *bgp = static_cast<BackgroundParser*>(m_scriptContext->GetBackgroundParser());
            Assert(bgp);
            this->WaitForBackgroundJobs(bgp, pse);
#endif
        }


        FinishDeferredFunction(pnodeProg->sxFnc.pnodeScopes);
    }

    if (pnodeGlobalEvalBlock)
    {
        FinishParseBlock(pnodeGlobalEvalBlock);
    }

    FinishParseBlock(pnodeGlobalBlock);

    m_scriptContext->AddSourceSize(m_length);

    if (m_parseType != ParseType_Deferred)
    {
        JS_ETW(EventWriteJSCRIPT_PARSE_METHOD_STOP(m_sourceContextInfo->dwHostSourceContext, GetScriptContext(), pnodeProg->sxFnc.functionId, *m_pCurrentAstSize, false, Js::Constants::GlobalFunction));
    }
    return pnodeProg;
}
