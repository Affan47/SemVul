ParseNodePtr Parser::ParseExpr(int oplMin,
    BOOL *pfCanAssign,
    BOOL fAllowIn,
    BOOL fAllowEllipsis,
    LPCOLESTR pNameHint,
    uint32 *pHintLength,
    uint32 *pShortNameOffset,
    _Inout_opt_ IdentToken* pToken,
    bool fUnaryOrParen,
    _Inout_opt_ bool* pfLikelyPattern,
    _Inout_opt_ charcount_t *plastRParen)
{
    Assert(pToken == nullptr || pToken->tk == tkNone);
    int opl;
    OpCode nop;
    charcount_t ichMin;
    ParseNodePtr pnode = nullptr;
    ParseNodePtr pnodeT = nullptr;
    BOOL fCanAssign = TRUE;
    bool assignmentStmt = false;
    bool fIsDotOrIndex = false;
    IdentToken term;
    RestorePoint termStart;
    uint32 hintLength = 0;
    uint32 hintOffset = 0;

    ParserState parserState;

    if (pHintLength != nullptr)
    {
        hintLength = *pHintLength;
    }

    if (pShortNameOffset != nullptr)
    {
        hintOffset = *pShortNameOffset;
    }

    EnsureStackAvailable();


    CaptureState(&parserState);

    m_pscan->Capture(&termStart);

    bool deferredErrorFoundOnLeftSide = false;
    bool savedDeferredInitError = m_hasDeferredShorthandInitError;
    m_hasDeferredShorthandInitError = false;


    if (m_phtbl->TokIsUnop(m_token.tk, &opl, &nop) && nop != knopNone)
    {
        IdentToken operandToken;
        ichMin = m_pscan->IchMinTok();

        if (nop == knopYield)
        {
            if (!m_pscan->YieldIsKeyword() || oplMin > opl)
            {


                Error(ERRsyntax);
            }
            if (m_currentScope->GetScopeType() == ScopeType_Parameter)
            {
                Error(ERRsyntax);
            }
        }
        else if (nop == knopAwait)
        {
            if (!m_pscan->AwaitIsKeyword() ||
                m_currentScope->GetScopeType() == ScopeType_Parameter)
            {


                Error(ERRBadAwait);
            }
        }

        m_pscan->Scan();

        if (m_token.tk == tkEllipsis) {

            Error(ERRUnexpectedEllipsis);
        }

        if (nop == knopYield && !m_pscan->FHadNewLine() && m_token.tk == tkStar)
        {
            m_pscan->Scan();
            nop = knopYieldStar;
        }

        if (nop == knopYield)
        {
            if (!ParseOptionalExpr<buildAST>(&pnodeT, false, opl, NULL, TRUE, fAllowEllipsis))
            {
                nop = knopYieldLeaf;
                if (buildAST)
                {
                    pnode = CreateNodeT<knopYieldLeaf>(ichMin, m_pscan->IchLimTok());
                }
            }
        }
        else
        {

            pnodeT = ParseExpr<buildAST>(opl, &fCanAssign, TRUE, FALSE, nullptr , nullptr , nullptr , &operandToken, true);
        }

        if (nop != knopYieldLeaf)
        {
            if (nop == knopIncPre || nop == knopDecPre)
            {
                if (!fCanAssign && PHASE_ON1(Js::EarlyReferenceErrorsPhase))
                {
                    Error(JSERR_CantAssignTo);
                }
                TrackAssignment<buildAST>(pnodeT, &operandToken);
                if (buildAST)
                {
                    if (IsStrictMode() && pnodeT->nop == knopName)
                    {
                        CheckStrictModeEvalArgumentsUsage(pnodeT->sxPid.pid);
                    }
                }
                else
                {
                    if (IsStrictMode() && operandToken.tk == tkID)
                    {
                        CheckStrictModeEvalArgumentsUsage(operandToken.pid);
                    }
                }
            }
            else if (nop == knopEllipsis)
            {
                if (!fAllowEllipsis)
                {
                    DeferOrEmitPotentialSpreadError(pnodeT);
                }
            }
            else if (m_token.tk == tkExpo)
            {

                Error(ERRInvalidUseofExponentiationOperator);
            }

            if (buildAST)
            {

                if (nop == knopPos && (pnodeT->nop == knopInt || pnodeT->nop == knopFlt) && !this->m_InAsmMode)
                {

                    pnode = pnodeT;
                }
                else if (nop == knopNeg &&
                    ((pnodeT->nop == knopInt && pnodeT->sxInt.lw != 0) ||
                    (pnodeT->nop == knopFlt && (pnodeT->sxFlt.dbl != 0 || this->m_InAsmMode))))
                {

                    pnode = pnodeT;
                    if (pnode->nop == knopInt)
                    {
                        pnode->sxInt.lw = -pnode->sxInt.lw;
                    }
                    else
                    {
                        pnode->sxFlt.dbl = -pnode->sxFlt.dbl;
                    }
                }
                else
                {
                    pnode = CreateUniNode(nop, pnodeT);
                    this->CheckArguments(pnode->sxUni.pnode1);
                }
                pnode->ichMin = ichMin;
            }

            if (nop == knopDelete)
            {
                if (IsStrictMode())
                {
                    if ((buildAST && pnode->sxUni.pnode1->nop == knopName) ||
                        (!buildAST && operandToken.tk == tkID))
                    {
                        Error(ERRInvalidDelete);
                    }
                }

                if (buildAST)
                {
                    ParseNodePtr pnode1 = pnode->sxUni.pnode1;
                    if (m_currentNodeFunc)
                    {
                        if (pnode1->nop == knopDot || pnode1->nop == knopIndex)
                        {


                            this->CheckArguments(pnode1->sxBin.pnode1);
                        }
                    }
                }
            }
        }

        fCanAssign = FALSE;
    }
    else
    {
        ichMin = m_pscan->IchMinTok();
        BOOL fLikelyPattern = FALSE;
        pnode = ParseTerm<buildAST>(TRUE, pNameHint, &hintLength, &hintOffset, &term, fUnaryOrParen, &fCanAssign, IsES6DestructuringEnabled() ? &fLikelyPattern : nullptr, &fIsDotOrIndex, plastRParen);
        if (pfLikelyPattern != nullptr)
        {
            *pfLikelyPattern = !!fLikelyPattern;
        }

        if (m_token.tk == tkDArrow)
        {
            m_hasDeferredShorthandInitError = false;
        }

        if (m_token.tk == tkAsg && oplMin <= koplAsg && fLikelyPattern)
        {
            m_pscan->SeekTo(termStart);


            int saveNextBlockId = m_nextBlockId;
            m_nextBlockId = parserState.m_nextBlockId;

            ParseDestructuredLiteralWithScopeSave(tkLCurly, false, false , DIC_ShouldNotParseInitializer);


            m_nextBlockId = saveNextBlockId;

            if (buildAST)
            {
                pnode = ConvertToPattern(pnode);
            }


            m_hasDeferredShorthandInitError = false;
        }

        if (buildAST)
        {
            pNameHint = NULL;
            if (pnode->nop == knopName)
            {
                pNameHint = pnode->sxPid.pid->Psz();
                hintLength = pnode->sxPid.pid->Cch();
                hintOffset = 0;
            }
            else if (pnode->nop == knopDot || pnode->nop == knopIndex)
            {
                if (CONFIG_FLAG(UseFullName))
                {
                    pNameHint = ConstructNameHint(pnode, &hintLength, &hintOffset);
                }
                else
                {
                    ParseNodePtr pnodeName = pnode;
                    while (pnodeName->nop == knopDot)
                    {
                        pnodeName = pnodeName->sxBin.pnode2;
                    }

                    if (pnodeName->nop == knopName)
                    {
                        pNameHint = pnodeName->sxPid.pid->Psz();
                        hintLength = pnodeName->sxPid.pid->Cch();
                        hintOffset = 0;
                    }
                }
            }
        }


        if (!m_pscan->FHadNewLine() &&
            (tkInc == m_token.tk || tkDec == m_token.tk))
        {
            if (!fCanAssign && PHASE_ON1(Js::EarlyReferenceErrorsPhase))
            {
                Error(JSERR_CantAssignTo);
            }
            TrackAssignment<buildAST>(pnode, &term);
            fCanAssign = FALSE;
            if (buildAST)
            {
                if (IsStrictMode() && pnode->nop == knopName)
                {
                    CheckStrictModeEvalArgumentsUsage(pnode->sxPid.pid);
                }
                this->CheckArguments(pnode);
                pnode = CreateUniNode(tkInc == m_token.tk ? knopIncPost : knopDecPost, pnode);
                pnode->ichLim = m_pscan->IchLimTok();
            }
            else
            {
                if (IsStrictMode() && term.tk == tkID)
                {
                    CheckStrictModeEvalArgumentsUsage(term.pid);
                }

                term.tk = tkNone;
            }
            m_pscan->Scan();
        }
    }

    deferredErrorFoundOnLeftSide = m_hasDeferredShorthandInitError;


    for (;;)
    {
        if (!m_phtbl->TokIsBinop(m_token.tk, &opl, &nop) || nop == knopNone)
        {
            break;
        }
        if ( ! fAllowIn && nop == knopIn )
        {
            break;
        }
        Assert(opl != koplNo);

        if (opl == koplAsg)
        {
            if (m_token.tk != tkDArrow)
            {


                Assert(ParseNode::Grfnop(nop) & fnopAsg || nop == knopFncDecl);
                TrackAssignment<buildAST>(pnode, &term);
                if (buildAST)
                {
                    if (IsStrictMode() && pnode->nop == knopName)
                    {
                        CheckStrictModeEvalArgumentsUsage(pnode->sxPid.pid);
                    }


                    if (nop == knopAsg && pnode->nop == knopDot && pnode->sxBin.pnode1->nop == knopThis && pnode->sxBin.pnode2->nop == knopName)
                    {
                        if (pnode->sxBin.pnode2->sxPid.pid != wellKnownPropertyPids.__proto__)
                        {
                            assignmentStmt = true;
                        }
                    }
                }
                else
                {
                    if (IsStrictMode() && term.tk == tkID)
                    {
                        CheckStrictModeEvalArgumentsUsage(term.pid);
                    }
                }
            }

            if (opl < oplMin)
            {
                break;
            }
            if (m_token.tk != tkDArrow && !fCanAssign && PHASE_ON1(Js::EarlyReferenceErrorsPhase))
            {
                Error(JSERR_CantAssignTo);

            }
        }
        else if (opl == koplExpo)
        {

            if (opl < oplMin)
            {
                break;
            }

        }
        else if (opl <= oplMin)
        {
            break;
        }


        term.tk = tkNone;


        m_pscan->Scan();
        fCanAssign = FALSE;


        if (nop == knopQmark)
        {
            pnodeT = ParseExpr<buildAST>(koplAsg, NULL, fAllowIn);
            ChkCurTok(tkColon, ERRnoColon);
            ParseNodePtr pnodeT2 = ParseExpr<buildAST>(koplAsg, NULL, fAllowIn);
            if (buildAST)
            {
                pnode = CreateTriNode(nop, pnode, pnodeT, pnodeT2);
                this->CheckArguments(pnode->sxTri.pnode2);
                this->CheckArguments(pnode->sxTri.pnode3);
            }
        }
        else if (nop == knopFncDecl)
        {
            ushort flags = fFncLambda;
            size_t iecpMin = 0;
            bool isAsyncMethod = false;

            RestoreStateFrom(&parserState);

            m_pscan->SeekTo(termStart);
            if (m_token.tk == tkID && m_token.GetIdentifier(m_phtbl) == wellKnownPropertyPids.async && m_scriptContext->GetConfig()->IsES7AsyncAndAwaitEnabled())
            {
                ichMin = m_pscan->IchMinTok();
                iecpMin = m_pscan->IecpMinTok();

                m_pscan->Scan();
                if ((m_token.tk == tkID || m_token.tk == tkLParen) && !m_pscan->FHadNewLine())
                {
                    flags |= fFncAsync;
                    isAsyncMethod = true;
                }
                else
                {
                    m_pscan->SeekTo(termStart);
                }
            }
            pnode = ParseFncDecl<buildAST>(flags, nullptr, false, false);
            if (isAsyncMethod)
            {
                pnode->sxFnc.cbMin = iecpMin;
                pnode->ichMin = ichMin;
            }
        }
        else
        {

            IdentToken token;
            pnodeT = ParseExpr<buildAST>(opl, NULL, fAllowIn, FALSE, pNameHint, &hintLength, &hintOffset, &token);


            if (fIsDotOrIndex && nop == knopAsg)
            {
                this->MarkEscapingRef(pnodeT, &token);
            }

            if (buildAST)
            {
                pnode = CreateBinNode(nop, pnode, pnodeT);
                Assert(pnode->sxBin.pnode2 != NULL);
                if (pnode->sxBin.pnode2->nop == knopFncDecl)
                {
                    Assert(hintLength >= hintOffset);
                    pnode->sxBin.pnode2->sxFnc.hint = pNameHint;
                    pnode->sxBin.pnode2->sxFnc.hintLength = hintLength;
                    pnode->sxBin.pnode2->sxFnc.hintOffset = hintOffset;

                    if (pnode->sxBin.pnode1->nop == knopDot)
                    {
                        pnode->sxBin.pnode2->sxFnc.isNameIdentifierRef  = false;
                    }
                    else if (pnode->sxBin.pnode1->nop == knopName)
                    {
                        PidRefStack *pidRef = pnode->sxBin.pnode1->sxPid.pid->GetTopRef();
                        pidRef->isFuncAssignment = true;
                    }
                }
                if (pnode->sxBin.pnode2->nop == knopClassDecl && pnode->sxBin.pnode1->nop == knopDot)
                {
                    Assert(pnode->sxBin.pnode2->sxClass.pnodeConstructor);
                    pnode->sxBin.pnode2->sxClass.pnodeConstructor->sxFnc.isNameIdentifierRef  = false;
                }
            }
            pNameHint = NULL;
        }
    }

    if (buildAST)
    {
        if (!assignmentStmt)
        {

            switch (pnode->nop)
            {
            case knopName:
            case knopInt:
            case knopFlt:
            case knopStr:
            case knopRegExp:
            case knopNull:
            case knopFalse:
            case knopTrue:
                break;
            default:
                if (m_currentNodeFunc)
                {
                    m_currentNodeFunc->sxFnc.SetHasNonThisStmt();
                }
                else if (m_currentNodeProg)
                {
                    m_currentNodeProg->sxFnc.SetHasNonThisStmt();
                }
            }
        }
    }

    if (m_hasDeferredShorthandInitError && !deferredErrorFoundOnLeftSide)
    {


        Error(ERRnoColon);
    }

    m_hasDeferredShorthandInitError = m_hasDeferredShorthandInitError || savedDeferredInitError;

    if (NULL != pfCanAssign)
    {
        *pfCanAssign = fCanAssign;
    }


    if (pToken && term.tk == tkID)
    {
        *pToken = term;
    }


    if (pnode != NULL)
    {
        uint nodeType = ParseNode::Grfnop(pnode->nop);
        if (nodeType & fnopAsg)
        {
            if (nodeType & fnopBin)
            {
                ParseNodePtr lhs = pnode->sxBin.pnode1;

                Assert(lhs);
                if (lhs->nop == knopDot)
                {
                    ParseNodePtr propertyNode = lhs->sxBin.pnode2;
                    if (propertyNode->nop == knopName)
                    {
                        propertyNode->sxPid.pid->PromoteAssignmentState();
                    }
                }
            }
            else if (nodeType & fnopUni)
            {

                ParseNodePtr lhs = pnode->sxUni.pnode1;
                if (lhs->nop == knopDot)
                {
                    ParseNodePtr propertyNode = lhs->sxBin.pnode2;
                    if (propertyNode->nop == knopName)
                    {
                        propertyNode->sxPid.pid->PromoteAssignmentState();
                    }
                }
            }
        }
    }
    return pnode;
}
