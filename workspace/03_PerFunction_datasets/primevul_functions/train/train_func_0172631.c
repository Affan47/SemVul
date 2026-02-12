ParseNodePtr Parser::ParseStringTemplateDecl(ParseNodePtr pnodeTagFnc)
{
    ParseNodePtr pnodeStringLiterals = nullptr;
    ParseNodePtr* lastStringLiteralNodeRef = nullptr;
    ParseNodePtr pnodeRawStringLiterals = nullptr;
    ParseNodePtr* lastRawStringLiteralNodeRef = nullptr;
    ParseNodePtr pnodeSubstitutionExpressions = nullptr;
    ParseNodePtr* lastSubstitutionExpressionNodeRef = nullptr;
    ParseNodePtr pnodeTagFncArgs = nullptr;
    ParseNodePtr* lastTagFncArgNodeRef = nullptr;
    ParseNodePtr stringLiteral = nullptr;
    ParseNodePtr stringLiteralRaw = nullptr;
    ParseNodePtr pnodeStringTemplate = nullptr;
    bool templateClosed = false;
    const bool isTagged = pnodeTagFnc != nullptr;
    uint16 stringConstantCount = 0;
    charcount_t ichMin = 0;

    Assert(m_token.tk == tkStrTmplBasic || m_token.tk == tkStrTmplBegin);

    if (buildAST)
    {
        pnodeStringTemplate = CreateNode(knopStrTemplate);
        pnodeStringTemplate->sxStrTemplate.countStringLiterals = 0;
        pnodeStringTemplate->sxStrTemplate.isTaggedTemplate = isTagged ? TRUE : FALSE;


        if (isTagged)
        {
            ichMin = pnodeTagFnc->ichMin;
            AddToNodeListEscapedUse(&pnodeTagFncArgs, &lastTagFncArgNodeRef, pnodeStringTemplate);
        }

    }
    CHAKRATEL_LANGSTATS_INC_LANGFEATURECOUNT(StringTemplates, m_scriptContext);

    OUTPUT_TRACE_DEBUGONLY(
        Js::StringTemplateParsePhase,
        _u("Starting to parse a string template (%s)...\n\tis tagged = %s\n"),
        GetParseType(),
        isTagged ? _u("true") : _u("false (Raw and cooked strings will not differ!)"));


    while (!templateClosed)
    {

        if (IsStrictMode() && m_pscan->IsOctOrLeadingZeroOnLastTKNumber())
        {
            Error(ERRES5NoOctal);
        }


        if (stringConstantCount >= USHRT_MAX)
        {
            Error(ERRnoMemory);
        }


        stringConstantCount++;


        if (buildAST)
        {
            stringLiteral = CreateStrNodeWithScanner(m_token.GetStr());

            AddToNodeList(&pnodeStringLiterals, &lastStringLiteralNodeRef, stringLiteral);


            if (isTagged)
            {

                IdentPtr pid = m_pscan->GetSecondaryBufferAsPid();

                stringLiteralRaw = CreateStrNodeWithScanner(pid);


                AddToNodeList(&pnodeRawStringLiterals, &lastRawStringLiteralNodeRef, stringLiteralRaw);
            }
            else
            {
#if DBG

                stringLiteralRaw = stringLiteral;
#endif
            }

            OUTPUT_TRACE_DEBUGONLY(
                Js::StringTemplateParsePhase,
                _u("Parsed string constant: \n\tcooked = \"%s\" \n\traw = \"%s\" \n\tdiffer = %d\n"),
                stringLiteral->sxPid.pid->Psz(),
                stringLiteralRaw->sxPid.pid->Psz(),
                stringLiteral->sxPid.pid->Psz() == stringLiteralRaw->sxPid.pid->Psz() ? 0 : 1);
        }

        switch (m_token.tk)
        {
        case tkStrTmplEnd:
        case tkStrTmplBasic:

            templateClosed = true;
            break;
        case tkStrTmplBegin:
        case tkStrTmplMid:
            {

            m_pscan->Scan();


            ParseNodePtr expression = ParseExpr<buildAST>(0);


            ChkCurTokNoScan(tkRCurly, ERRnoRcurly);


            m_pscan->SetScanState(Scanner_t::ScanState::ScanStateStringTemplateMiddleOrEnd);
            m_pscan->Scan();

            if (buildAST)
            {

                if (isTagged)
                {
                    AddToNodeListEscapedUse(&pnodeTagFncArgs, &lastTagFncArgNodeRef, expression);
                }
                else
                {


                    AddToNodeList(&pnodeSubstitutionExpressions, &lastSubstitutionExpressionNodeRef, expression);
                }
            }

            if (!(m_token.tk == tkStrTmplMid || m_token.tk == tkStrTmplEnd))
            {


                Assert(m_token.tk == tkEOF || m_token.tk == tkScanError);
                Error(ERRsyntax);
            }

            OUTPUT_TRACE_DEBUGONLY(Js::StringTemplateParsePhase, _u("Parsed expression\n"));
            }
            break;
        default:
            Assert(false);
            break;
        }
    }

    if (buildAST)
    {
        pnodeStringTemplate->sxStrTemplate.pnodeStringLiterals = pnodeStringLiterals;
        pnodeStringTemplate->sxStrTemplate.pnodeStringRawLiterals = pnodeRawStringLiterals;
        pnodeStringTemplate->sxStrTemplate.pnodeSubstitutionExpressions = pnodeSubstitutionExpressions;
        pnodeStringTemplate->sxStrTemplate.countStringLiterals = stringConstantCount;


        pnodeStringTemplate->ichLim = stringLiteral->ichLim;


        if (isTagged)
        {

            pnodeStringTemplate = CreateCallNode(knopCall, pnodeTagFnc, pnodeTagFncArgs, ichMin, pnodeStringTemplate->ichLim);


            pnodeStringTemplate->sxCall.argCount = stringConstantCount;
        }
    }

    m_pscan->Scan();

    return pnodeStringTemplate;
}
