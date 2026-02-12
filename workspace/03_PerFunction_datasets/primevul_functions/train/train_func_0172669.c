ParseNodePtr Parser::CreateVarDeclNode(IdentPtr pid, SymbolType symbolType, bool autoArgumentsObject, ParseNodePtr pnodeFnc, bool errorOnRedecl, bool *isRedecl)
{
    ParseNodePtr pnode = CreateDeclNode(knopVarDecl, pid, symbolType, errorOnRedecl, isRedecl);


    AssertMem(m_ppnodeVar);
    pnode->sxVar.pnodeNext = *m_ppnodeVar;
    *m_ppnodeVar = pnode;
    if (nullptr != pid)
    {

        AssertMem(pid);
        m_ppnodeVar = &pnode->sxVar.pnodeNext;
        CheckPidIsValid(pid, autoArgumentsObject);
    }

    return pnode;
}
