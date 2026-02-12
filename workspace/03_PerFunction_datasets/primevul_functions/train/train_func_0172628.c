ParseNodePtr Parser::ParseTerm(BOOL fAllowCall,
    LPCOLESTR pNameHint,
    uint32 *pHintLength,
    uint32 *pShortNameOffset,
    _Inout_opt_ IdentToken* pToken ,
    bool fUnaryOrParen ,
    _Out_opt_ BOOL* pfCanAssign ,
    _Inout_opt_ BOOL* pfLikelyPattern ,
    _Out_opt_ bool* pfIsDotOrIndex ,
    _Inout_opt_ charcount_t *plastRParen )
{
    ParseNodePtr pnode = nullptr;
    PidRefStack *savedTopAsyncRef = nullptr;
    charcount_t ichMin = 0;
    size_t iecpMin = 0;
    size_t iuMin;
    IdentToken term;
    BOOL fInNew = FALSE;
    BOOL fCanAssign = TRUE;
    bool isAsyncExpr = false;
    bool isLambdaExpr = false;
    Assert(pToken == nullptr || pToken->tk == tkNone);

    if (this->IsBackgroundParser())
    {
        PROBE_STACK_NO_DISPOSE(m_scriptContext, Js::Constants::MinStackParseOneTerm);
    }
    else
    {
        PROBE_STACK(m_scriptContext, Js::Constants::MinStackParseOneTerm);
    }

    switch (m_token.tk)
    {
    case tkID:
    {
        PidRefStack *ref = nullptr;
        IdentPtr pid = m_token.GetIdentifier(m_phtbl);
        charcount_t ichLim = m_pscan->IchLimTok();
        size_t iecpLim = m_pscan->IecpLimTok();
        ichMin = m_pscan->IchMinTok();
        iecpMin  = m_pscan->IecpMinTok();

        if (pid == wellKnownPropertyPids.async &&
            m_scriptContext->GetConfig()->IsES7AsyncAndAwaitEnabled())
        {
            isAsyncExpr = true;
        }

        bool previousAwaitIsKeyword = m_pscan->SetAwaitIsKeyword(isAsyncExpr);
        m_pscan->Scan();
        m_pscan->SetAwaitIsKeyword(previousAwaitIsKeyword);


        if (isAsyncExpr && !m_pscan->FHadNewLine())
        {
            if (m_token.tk == tkFUNCTION)
            {
                goto LFunction;
            }
            else if (m_token.tk == tkID || m_token.tk == tkAWAIT)
            {
                isLambdaExpr = true;
                goto LFunction;
            }
            else if (m_token.tk == tkLParen)
            {


                savedTopAsyncRef = pid->GetTopRef();
            }
        }


        if (m_token.tk != tkDArrow)
        {
            ref = this->PushPidRef(pid);
        }

        if (buildAST)
        {
            pnode = CreateNameNode(pid);
            pnode->ichMin = ichMin;
            pnode->ichLim = ichLim;
            pnode->sxPid.SetSymRef(ref);
        }
        else
        {

            term.tk = tkID;
            term.pid = pid;
            term.ichMin = static_cast<charcount_t>(iecpMin);
            term.ichLim = static_cast<charcount_t>(iecpLim);
        }
        CheckArgumentsUse(pid, GetCurrentFunctionNode());
        break;
    }

    case tkTHIS:
        if (buildAST)
        {
            pnode = CreateNodeWithScanner<knopThis>();
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkLParen:
    {
        ichMin = m_pscan->IchMinTok();
        iuMin = m_pscan->IecpMinTok();
        m_pscan->Scan();
        if (m_token.tk == tkRParen)
        {


            fAllowCall = FALSE;
            m_pscan->Scan();


            if (!m_doingFastScan && (m_token.tk != tkDArrow || m_pscan->FHadNewLine()))
            {
                Error(ERRsyntax);
            }

            if (buildAST)
            {
                pnode = CreateNodeWithScanner<knopEmpty>();
            }
            break;
        }


        uint saveNextBlockId = m_nextBlockId;
        uint saveCurrBlockId = GetCurrentBlock()->sxBlock.blockId;
        GetCurrentBlock()->sxBlock.blockId = m_nextBlockId++;

        this->m_parenDepth++;
        pnode = ParseExpr<buildAST>(koplNo, &fCanAssign, TRUE, FALSE, nullptr, nullptr , nullptr  , &term, true, nullptr, plastRParen);
        this->m_parenDepth--;

        if (buildAST && plastRParen)
        {
            *plastRParen = m_pscan->IchLimTok();
        }

        ChkCurTok(tkRParen, ERRnoRparen);

        GetCurrentBlock()->sxBlock.blockId = saveCurrBlockId;
        if (m_token.tk == tkDArrow)
        {


            m_nextBlockId = saveNextBlockId;
        }


        if (m_deferEllipsisError && m_token.tk != tkDArrow)
        {
            m_pscan->SeekTo(m_EllipsisErrLoc);
            Error(ERRInvalidSpreadUse);
        }
        else
        {
            m_deferEllipsisError = false;
        }
        break;
    }

    case tkIntCon:
        if (IsStrictMode() && m_pscan->IsOctOrLeadingZeroOnLastTKNumber())
        {
            Error(ERRES5NoOctal);
        }

        if (buildAST)
        {
            pnode = CreateIntNodeWithScanner(m_token.GetLong());
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkFltCon:
        if (IsStrictMode() && m_pscan->IsOctOrLeadingZeroOnLastTKNumber())
        {
            Error(ERRES5NoOctal);
        }

        if (buildAST)
        {
            pnode = CreateNodeWithScanner<knopFlt>();
            pnode->sxFlt.dbl = m_token.GetDouble();
            pnode->sxFlt.maybeInt = m_token.GetDoubleMayBeInt();
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkStrCon:
        if (IsStrictMode() && m_pscan->IsOctOrLeadingZeroOnLastTKNumber())
        {
            Error(ERRES5NoOctal);
        }

        if (buildAST)
        {
            pnode = CreateStrNodeWithScanner(m_token.GetStr());
        }
        else
        {


            this->ReduceDeferredScriptLength(m_pscan->IchLimTok() - m_pscan->IchMinTok());
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkTRUE:
        if (buildAST)
        {
            pnode = CreateNodeWithScanner<knopTrue>();
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkFALSE:
        if (buildAST)
        {
            pnode = CreateNodeWithScanner<knopFalse>();
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkNULL:
        if (buildAST)
        {
            pnode = CreateNodeWithScanner<knopNull>();
        }
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkDiv:
    case tkAsgDiv:
        pnode = ParseRegExp<buildAST>();
        fCanAssign = FALSE;
        m_pscan->Scan();
        break;

    case tkNEW:
    {
        ichMin = m_pscan->IchMinTok();
        m_pscan->Scan();

        if (m_token.tk == tkDot && m_scriptContext->GetConfig()->IsES6ClassAndExtendsEnabled())
        {
            pnode = ParseMetaProperty<buildAST>(tkNEW, ichMin, &fCanAssign);

            m_pscan->Scan();
        }
        else
        {
            ParseNodePtr pnodeExpr = ParseTerm<buildAST>(FALSE, pNameHint, pHintLength, pShortNameOffset);
            if (buildAST)
            {
                pnode = CreateCallNode(knopNew, pnodeExpr, nullptr);
                pnode->ichMin = ichMin;
            }
            fInNew = TRUE;
            fCanAssign = FALSE;
        }
        break;
    }

    case tkLBrack:
    {
        ichMin = m_pscan->IchMinTok();
        m_pscan->Scan();
        pnode = ParseArrayLiteral<buildAST>();
        if (buildAST)
        {
            pnode->ichMin = ichMin;
            pnode->ichLim = m_pscan->IchLimTok();
        }

        if (this->m_arrayDepth == 0)
        {
            Assert(m_pscan->IchLimTok() - ichMin > m_funcInArray);
            this->ReduceDeferredScriptLength(m_pscan->IchLimTok() - ichMin - this->m_funcInArray);
            this->m_funcInArray = 0;
            this->m_funcInArrayDepth = 0;
        }
        ChkCurTok(tkRBrack, ERRnoRbrack);
        if (!IsES6DestructuringEnabled())
        {
            fCanAssign = FALSE;
        }
        else if (pfLikelyPattern != nullptr && !IsPostFixOperators())
        {
            *pfLikelyPattern = TRUE;
        }
        break;
    }

    case tkLCurly:
    {
        ichMin = m_pscan->IchMinTok();
        m_pscan->ScanForcingPid();
        ParseNodePtr pnodeMemberList = ParseMemberList<buildAST>(pNameHint, pHintLength);
        if (buildAST)
        {
            pnode = CreateUniNode(knopObject, pnodeMemberList);
            pnode->ichMin = ichMin;
            pnode->ichLim = m_pscan->IchLimTok();
        }
        ChkCurTok(tkRCurly, ERRnoRcurly);
        if (!IsES6DestructuringEnabled())
        {
            fCanAssign = FALSE;
        }
        else if (pfLikelyPattern != nullptr && !IsPostFixOperators())
        {
            *pfLikelyPattern = TRUE;
        }
        break;
    }

    case tkFUNCTION:
    {
LFunction :
        if (m_grfscr & fscrDeferredFncExpression)
        {


            m_grfscr &= ~fscrDeferredFncExpression;
        }
        ushort flags = fFncNoFlgs;
        if (isLambdaExpr)
        {
            flags |= fFncLambda;
        }
        if (isAsyncExpr)
        {
            flags |= fFncAsync;
        }
        pnode = ParseFncDecl<buildAST>(flags, pNameHint, false, true, fUnaryOrParen);
        if (isAsyncExpr)
        {
            pnode->sxFnc.cbMin = iecpMin;
            pnode->ichMin = ichMin;
        }
        fCanAssign = FALSE;
        break;
    }

    case tkCLASS:
        if (m_scriptContext->GetConfig()->IsES6ClassAndExtendsEnabled())
        {
            pnode = ParseClassDecl<buildAST>(FALSE, pNameHint, pHintLength, pShortNameOffset);
        }
        else
        {
            goto LUnknown;
        }
        fCanAssign = FALSE;
        break;

    case tkStrTmplBasic:
    case tkStrTmplBegin:
        pnode = ParseStringTemplateDecl<buildAST>(nullptr);
        fCanAssign = FALSE;
        break;

    case tkSUPER:
        if (m_scriptContext->GetConfig()->IsES6ClassAndExtendsEnabled())
        {
            pnode = ParseSuper<buildAST>(pnode, !!fAllowCall);
        }
        else
        {
            goto LUnknown;
        }
        break;

    case tkCASE:
    {
        if (!m_doingFastScan)
        {
            goto LUnknown;
        }
        ParseNodePtr pnodeUnused;
        pnode = ParseCase<buildAST>(&pnodeUnused);
        break;
    }

    case tkELSE:
        if (!m_doingFastScan)
        {
            goto LUnknown;
        }
        m_pscan->Scan();
        ParseStatement<buildAST>();
        break;

    default:
    LUnknown :
        Error(ERRsyntax);
        break;
    }

    pnode = ParsePostfixOperators<buildAST>(pnode, fAllowCall, fInNew, isAsyncExpr, &fCanAssign, &term, pfIsDotOrIndex);

    if (savedTopAsyncRef != nullptr &&
        this->m_token.tk == tkDArrow)
    {


        for (IdentPtr pid = wellKnownPropertyPids.async; pid->GetTopRef() != savedTopAsyncRef;)
        {
            Assert(pid->GetTopRef() != nullptr);
            pid->RemovePrevPidRef(nullptr);
        }
    }


    if (pToken && term.tk == tkID)
    {
        *pToken = term;
    }

    if (pfCanAssign)
    {
        *pfCanAssign = fCanAssign;
    }

    return pnode;
}
