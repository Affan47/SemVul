void Parser::AddArgumentsNodeToVars(ParseNodePtr pnodeFnc)
{
    if((pnodeFnc->grfpn & PNodeFlags::fpnArguments_overriddenByDecl) || pnodeFnc->sxFnc.IsLambda())
    {


        pnodeFnc->sxFnc.SetHasReferenceableBuiltInArguments(false);
    }
    else
    {
        ParseNodePtr argNode = nullptr;
        if(m_ppnodeVar == &pnodeFnc->sxFnc.pnodeVars)
        {

            argNode = CreateVarDeclNode(wellKnownPropertyPids.arguments, STVariable, true, pnodeFnc);
        }
        else
        {


            ParseNodePtr *const ppnodeVarSave = m_ppnodeVar;
            m_ppnodeVar = &pnodeFnc->sxFnc.pnodeVars;
            argNode = CreateVarDeclNode(wellKnownPropertyPids.arguments, STVariable, true, pnodeFnc);
            m_ppnodeVar = ppnodeVarSave;
        }

        Assert(argNode);
        argNode->grfpn |= PNodeFlags::fpnArguments;


        argNode->sxVar.sym->SetDecl(argNode);

        pnodeFnc->sxFnc.SetHasReferenceableBuiltInArguments(true);
    }
}
