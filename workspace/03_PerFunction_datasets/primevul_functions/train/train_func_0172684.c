void Parser::AddVarDeclToBlock(ParseNode *pnode)
{
    Assert(pnode->nop == knopConstDecl || pnode->nop == knopLetDecl);


    AssertMem(m_currentBlockInfo->m_ppnodeLex);
    *m_currentBlockInfo->m_ppnodeLex = pnode;
    m_currentBlockInfo->m_ppnodeLex = &pnode->sxVar.pnodeNext;
    pnode->sxVar.pnodeNext = nullptr;
}
