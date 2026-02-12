ParseNodePtr Parser::ParseDestructuredVarDecl(tokens declarationType, bool isDecl, bool *hasSeenRest, bool topLevel, bool allowEmptyExpression)
{
    ParseNodePtr pnodeElem = nullptr;
    int parenCount = 0;
    bool seenRest = false;


    int originalCurrentBlockId = GetCurrentBlock()->sxBlock.blockId;


    if (!isDecl)
    {
        while (m_token.tk == tkLParen)
        {
            m_pscan->Scan();
            ++parenCount;


            GetCurrentBlock()->sxBlock.blockId = m_nextBlockId++;
        }
    }

    if (m_token.tk == tkEllipsis)
    {


        seenRest = true;
        m_pscan->Scan();


        if (!isDecl)
        {
            while (m_token.tk == tkLParen)
            {
                m_pscan->Scan();
                ++parenCount;


                GetCurrentBlock()->sxBlock.blockId = m_nextBlockId++;
            }
        }

        if (m_token.tk != tkID && m_token.tk != tkSUPER && m_token.tk != tkLCurly && m_token.tk != tkLBrack)
        {
            if (isDecl)
            {
                Error(ERRnoIdent);
            }
            else
            {
                Error(ERRInvalidAssignmentTarget);
            }
        }
    }

    if (IsPossiblePatternStart())
    {

        pnodeElem = ParseDestructuredLiteral<buildAST>(declarationType, isDecl, false , seenRest ? DIC_ShouldNotParseInitializer : DIC_None);
        if (!isDecl)
        {
            BOOL fCanAssign;
            IdentToken token;

            pnodeElem = ParsePostfixOperators<buildAST>(pnodeElem, TRUE, FALSE, FALSE, &fCanAssign, &token);
        }
    }
    else if (m_token.tk == tkSUPER || m_token.tk == tkID)
    {
        if (isDecl)
        {
            charcount_t ichMin = m_pscan->IchMinTok();
            pnodeElem = ParseVariableDeclaration<buildAST>(declarationType, ichMin
                ,false, nullptr, true, !seenRest, false );

        }
        else
        {
            BOOL fCanAssign;
            IdentToken token;

            pnodeElem = ParseTerm<buildAST>( m_token.tk != tkSUPER, nullptr , nullptr , nullptr , &token, false,
                                                             &fCanAssign);


            if (!fCanAssign)
            {
                Error(ERRInvalidAssignmentTarget);
            }

            if (buildAST)
            {
                if (IsStrictMode() && pnodeElem != nullptr && pnodeElem->nop == knopName)
                {
                    CheckStrictModeEvalArgumentsUsage(pnodeElem->sxPid.pid);
                }
            }
            else
            {
                if (IsStrictMode() && token.tk == tkID)
                {
                    CheckStrictModeEvalArgumentsUsage(token.pid);
                }
                token.tk = tkNone;
            }
        }
    }
    else if (!((m_token.tk == tkComma || m_token.tk == tkRBrack || m_token.tk == tkRCurly) && allowEmptyExpression))
    {
        if (m_token.IsOperator())
        {
            Error(ERRDestructNoOper);
        }
        Error(ERRDestructIDRef);
    }


    if (!isDecl)
    {
        while (m_token.tk == tkRParen)
        {
            m_pscan->Scan();
            --parenCount;
        }
    }

    if (hasSeenRest != nullptr)
    {
        *hasSeenRest = seenRest;
    }

    if (m_token.tk == tkAsg)
    {

        if (seenRest)
        {
            Error(ERRRestWithDefault);
        }
        m_pscan->Scan();

        bool alreadyHasInitError = m_hasDeferredShorthandInitError;
        ParseNodePtr pnodeInit = ParseExpr<buildAST>(koplCma);

        if (m_hasDeferredShorthandInitError && !alreadyHasInitError)
        {
            Error(ERRnoColon);
        }

        if (buildAST)
        {
            pnodeElem = CreateBinNode(knopAsg, pnodeElem, pnodeInit);
        }
    }

    if (buildAST && seenRest)
    {
        ParseNodePtr pnodeRest = CreateNodeWithScanner<knopEllipsis>();
        pnodeRest->sxUni.pnode1 = pnodeElem;
        pnodeElem = pnodeRest;
    }


    if (!isDecl)
    {
        while (m_token.tk == tkRParen)
        {
            m_pscan->Scan();
            --parenCount;
        }


        GetCurrentBlock()->sxBlock.blockId = originalCurrentBlockId;
    }

    if (!(m_token.tk == tkComma || m_token.tk == tkRBrack || m_token.tk == tkRCurly))
    {
        if (m_token.IsOperator())
        {
            Error(ERRDestructNoOper);
        }
        Error(ERRsyntax);
    }

    if (parenCount != 0)
    {
        Error(ERRnoRparen);
    }
    return pnodeElem;
}
