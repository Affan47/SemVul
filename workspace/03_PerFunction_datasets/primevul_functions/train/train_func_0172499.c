ParseNodePtr Parser::ParseSuper(ParseNodePtr pnode, bool fAllowCall)
{
    ParseNodePtr currentNodeFunc = GetCurrentFunctionNode();

    if (buildAST) {
        pnode = CreateNodeWithScanner<knopSuper>();
    }

    m_pscan->ScanForcingPid();

    switch (m_token.tk)
    {
    case tkDot:
    case tkLBrack:
    case tkLParen:
        break;

    default:
        Error(ERRInvalidSuper);
        break;
    }

    if (!fAllowCall && (m_token.tk == tkLParen))
    {
        Error(ERRInvalidSuper);
    }
    else if (this->m_parsingSuperRestrictionState == ParsingSuperRestrictionState_SuperCallAndPropertyAllowed)
    {

    }
    else if (this->m_parsingSuperRestrictionState == ParsingSuperRestrictionState_SuperPropertyAllowed)
    {
        if (m_token.tk == tkLParen)
        {
            if ((this->m_grfscr & fscrEval) == fscrNil)
            {

                Error(ERRInvalidSuper);
            }
            else
            {
                Js::JavascriptFunction * caller = nullptr;
                if (Js::JavascriptStackWalker::GetCaller(&caller, m_scriptContext))
                {
                    Js::FunctionBody * callerBody = caller->GetFunctionBody();
                    Assert(callerBody);
                    if (!callerBody->GetFunctionInfo()->GetAllowDirectSuper())
                    {
                        Error(ERRInvalidSuper);
                    }
                }
            }
        }
    }
    else
    {

        Error(ERRInvalidSuper);
    }

    currentNodeFunc->sxFnc.SetHasSuperReference(TRUE);
    CHAKRATEL_LANGSTATS_INC_LANGFEATURECOUNT(Super, m_scriptContext);
    return pnode;
}
