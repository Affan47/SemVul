bool Parser::IsImportOrExportStatementValidHere()
{
    ParseNodePtr curFunc = GetCurrentFunctionNode();


    return curFunc->nop == knopFncDecl
        && curFunc->sxFnc.IsModule()
        && this->m_currentBlockInfo->pnodeBlock == curFunc->sxFnc.pnodeBodyScope
        && (this->m_grfscr & fscrEvalCode) != fscrEvalCode
        && this->m_tryCatchOrFinallyDepth == 0;
}
