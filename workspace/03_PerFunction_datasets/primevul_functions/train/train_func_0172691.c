bool Parser::ParseFncNames(ParseNodePtr pnodeFnc, ParseNodePtr pnodeFncParent, ushort flags, ParseNodePtr **pLastNodeRef)
{
    BOOL fDeclaration = flags & fFncDeclaration;
    BOOL fIsAsync = flags & fFncAsync;
    ParseNodePtr pnodeT;
    charcount_t ichMinNames, ichLimNames;


    m_pscan->Scan();


    if (flags & fFncGenerator)
    {
        Assert(m_scriptContext->GetConfig()->IsES6GeneratorsEnabled());
        pnodeFnc->sxFnc.SetIsGenerator();
    }
    else if (m_scriptContext->GetConfig()->IsES6GeneratorsEnabled() &&
        m_token.tk == tkStar &&
        !(flags & fFncClassMember))
    {
        if (!fDeclaration)
        {
            bool fPreviousYieldIsKeyword = m_pscan->SetYieldIsKeyword(!fDeclaration);
            m_pscan->Scan();
            m_pscan->SetYieldIsKeyword(fPreviousYieldIsKeyword);
        }
        else
        {
            m_pscan->Scan();
        }

        pnodeFnc->sxFnc.SetIsGenerator();
    }

    if (fIsAsync)
    {
        if (pnodeFnc->sxFnc.IsGenerator())
        {
            Error(ERRsyntax);
        }
        pnodeFnc->sxFnc.SetIsAsync();
    }

    if (pnodeFnc)
    {
        pnodeFnc->sxFnc.pnodeName = nullptr;
    }

    if ((m_token.tk != tkID || flags & fFncNoName)
        && (IsStrictMode() || (pnodeFnc && pnodeFnc->sxFnc.IsGenerator()) || m_token.tk != tkYIELD || fDeclaration))
    {
        if (fDeclaration  ||
            m_token.IsReservedWord())
        {
            IdentifierExpectedError(m_token);
        }
        return false;
    }

    ichMinNames = m_pscan->IchMinTok();


    Assert(m_token.tk == tkID || (m_token.tk == tkYIELD && !fDeclaration));

    if (IsStrictMode())
    {
        CheckStrictModeEvalArgumentsUsage(m_token.GetIdentifier(m_phtbl));
    }
    Token tokenBase = m_token;
    charcount_t ichMinBase = m_pscan->IchMinTok();
    charcount_t ichLimBase = m_pscan->IchLimTok();

    m_pscan->Scan();

    IdentPtr pidBase = tokenBase.GetIdentifier(m_phtbl);
    pnodeT = CreateDeclNode(knopVarDecl, pidBase, STFunction);
    pnodeT->ichMin = ichMinBase;
    pnodeT->ichLim = ichLimBase;

    if (fDeclaration &&
        pnodeFncParent &&
        pnodeFncParent->sxFnc.pnodeName &&
        pnodeFncParent->sxFnc.pnodeName->nop == knopVarDecl &&
        pnodeFncParent->sxFnc.pnodeName->sxVar.pid == pidBase)
    {
        pnodeFncParent->sxFnc.SetNameIsHidden();
    }

    if (buildAST)
    {
        AnalysisAssert(pnodeFnc);
        ichLimNames = pnodeT->ichLim;
        AddToNodeList(&pnodeFnc->sxFnc.pnodeName, pLastNodeRef, pnodeT);

        pnodeFnc->sxFnc.pnodeName->ichMin = ichMinNames;
        pnodeFnc->sxFnc.pnodeName->ichLim = ichLimNames;
        if (knopVarDecl == pnodeFnc->sxFnc.pnodeName->nop)
        {

            pnodeFnc->sxFnc.pid = pnodeFnc->sxFnc.pnodeName->sxVar.pid;
        }
        else
        {

            pnodeFnc->sxFnc.pid = m_phtbl->PidHashNameLen(
                m_pscan->PchBase() + ichMinNames,
                m_pscan->AdjustedLast(),
                ichLimNames - ichMinNames);
        }
    }

    return true;
}
