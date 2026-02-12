ParseNodePtr Parser::ParsePostfixOperators(
    ParseNodePtr pnode,
    BOOL fAllowCall,
    BOOL fInNew,
    BOOL isAsyncExpr,
    BOOL *pfCanAssign,
    _Inout_ IdentToken* pToken,
    _Out_opt_ bool* pfIsDotOrIndex )
{
    uint16 count = 0;
    bool callOfConstants = false;
    if (pfIsDotOrIndex)
    {
        *pfIsDotOrIndex = false;
    }

    for (;;)
    {
        uint16 spreadArgCount = 0;
        switch (m_token.tk)
        {
        case tkLParen:
            {
                if (fInNew)
                {
                    ParseNodePtr pnodeArgs = ParseArgList<buildAST>(&callOfConstants, &spreadArgCount, &count);
                    if (buildAST)
                    {
                        Assert(pnode->nop == knopNew);
                        Assert(pnode->sxCall.pnodeArgs == nullptr);
                        pnode->sxCall.pnodeArgs = pnodeArgs;
                        pnode->sxCall.callOfConstants = callOfConstants;
                        pnode->sxCall.isApplyCall = false;
                        pnode->sxCall.isEvalCall = false;
                        pnode->sxCall.argCount = count;
                        pnode->sxCall.spreadArgCount = spreadArgCount;
                        pnode->ichLim = m_pscan->IchLimTok();
                    }
                    else
                    {
                        pnode = nullptr;
                        pToken->tk = tkNone;
                    }
                    fInNew = FALSE;
                    ChkCurTok(tkRParen, ERRnoRparen);
                }
                else
                {
                    bool fCallIsEval = false;
                    if (!fAllowCall)
                    {
                        return pnode;
                    }

                    uint saveNextBlockId = m_nextBlockId;
                    uint saveCurrBlockId = GetCurrentBlock()->sxBlock.blockId;

                    if (isAsyncExpr)
                    {


                        GetCurrentBlock()->sxBlock.blockId = m_nextBlockId++;
                    }

                    ParseNodePtr pnodeArgs = ParseArgList<buildAST>(&callOfConstants, &spreadArgCount, &count);


                    if (buildAST)
                    {
                        pnode = CreateCallNode(knopCall, pnode, pnodeArgs);
                        Assert(pnode);


                        if (count > 0 && this->NodeIsEvalName(pnode->sxCall.pnodeTarget))
                        {
                            this->MarkEvalCaller();
                            fCallIsEval = true;
                        }

                        pnode->sxCall.callOfConstants = callOfConstants;
                        pnode->sxCall.spreadArgCount = spreadArgCount;
                        pnode->sxCall.isApplyCall = false;
                        pnode->sxCall.isEvalCall = fCallIsEval;
                        pnode->sxCall.argCount = count;
                        pnode->ichLim = m_pscan->IchLimTok();
                    }
                    else
                    {
                        pnode = nullptr;
                        if (pToken->tk == tkID && pToken->pid == wellKnownPropertyPids.eval && count > 0)
                        {
                            this->MarkEvalCaller();
                        }
                        pToken->tk = tkNone;
                    }

                    ChkCurTok(tkRParen, ERRnoRparen);

                    if (isAsyncExpr)
                    {
                        GetCurrentBlock()->sxBlock.blockId = saveCurrBlockId;
                        if (m_token.tk == tkDArrow)
                        {


                            m_nextBlockId = saveNextBlockId;
                        }
                    }
                }
                if (pfCanAssign)
                {
                    *pfCanAssign = FALSE;
                }
                if (pfIsDotOrIndex)
                {
                    *pfIsDotOrIndex = false;
                }
                break;
            }
        case tkLBrack:
            {
                m_pscan->Scan();
                ParseNodePtr pnodeExpr = ParseExpr<buildAST>();
                if (buildAST)
                {
                    pnode = CreateBinNode(knopIndex, pnode, pnodeExpr);
                    pnode->ichLim = m_pscan->IchLimTok();
                }
                else
                {
                    pnode = nullptr;
                    pToken->tk = tkNone;
                }
                ChkCurTok(tkRBrack, ERRnoRbrack);
                if (pfCanAssign)
                {
                    *pfCanAssign = TRUE;
                }
                if (pfIsDotOrIndex)
                {
                    *pfIsDotOrIndex = true;
                }

                if (!buildAST)
                {
                    break;
                }

                bool shouldConvertToDot = false;
                if (pnode->sxBin.pnode2->nop == knopStr)
                {

                    shouldConvertToDot = pnode->sxBin.pnode2->sxPid.pid->Cch() > 0 && !m_pscan->IsEscapeOnLastTkStrCon();
                }

                if (shouldConvertToDot)
                {
                    LPCOLESTR str = pnode->sxBin.pnode2->sxPid.pid->Psz();


                    uint32 uintValue;
                    if(Js::JavascriptOperators::TryConvertToUInt32(
                           str,
                           pnode->sxBin.pnode2->sxPid.pid->Cch(),
                           &uintValue) &&
                       !Js::TaggedInt::IsOverflow(uintValue))
                    {

                        auto intNode = CreateIntNodeWithScanner(uintValue);
                        pnode->sxBin.pnode2 = intNode;
                    }


                    else
                    {
                        bool doConvertToProperty = false;
                        if (!Parser::IsNaNOrInfinityLiteral<true>(str))
                        {
                            const OLECHAR* terminalChar;
                            double dbl = Js::NumberUtilities::StrToDbl(str, &terminalChar, m_scriptContext);
                            bool convertsToFloat = !Js::NumberUtilities::IsNan(dbl);
                            doConvertToProperty = !convertsToFloat;
                        }

                        if (doConvertToProperty)
                        {
                            pnode->sxBin.pnode2->nop = knopName;
                            pnode->nop = knopDot;
                            pnode->grfpn |= PNodeFlags::fpnIndexOperator;
                        }
                    }
                }
            }
            break;

        case tkDot:
            {
            ParseNodePtr name = nullptr;
            OpCode opCode = knopDot;

            m_pscan->Scan();
            if (!m_token.IsIdentifier())
            {

                if (!(m_token.IsReservedWord()))
                {
                    IdentifierExpectedError(m_token);
                }
            }


            else if (buildAST && Parser::IsNaNOrInfinityLiteral<false>(m_token.GetIdentifier(m_phtbl)->Psz()))
            {
                opCode = knopIndex;
            }

            if (buildAST)
            {
                if (opCode == knopDot)
                {
                    name = CreateNameNode(m_token.GetIdentifier(m_phtbl));
                }
                else
                {
                    Assert(opCode == knopIndex);
                    name = CreateStrNodeWithScanner(m_token.GetIdentifier(m_phtbl));
                }
                pnode = CreateBinNode(opCode, pnode, name);
            }
            else
            {
                pnode = nullptr;
                pToken->tk = tkNone;
            }

            if (pfCanAssign)
            {
                *pfCanAssign = TRUE;
            }
            if (pfIsDotOrIndex)
            {
                *pfIsDotOrIndex = true;
            }
            m_pscan->Scan();

            break;
            }

        case tkStrTmplBasic:
        case tkStrTmplBegin:
            {
                ParseNode* templateNode = ParseStringTemplateDecl<buildAST>(pnode);

                if (!buildAST)
                {
                    pToken->tk = tkNone;
                }

                pnode = templateNode;
                if (pfCanAssign)
                {
                    *pfCanAssign = FALSE;
                }
                if (pfIsDotOrIndex)
                {
                    *pfIsDotOrIndex = false;
                }
                break;
            }
        default:
            return pnode;
        }
    }
}
