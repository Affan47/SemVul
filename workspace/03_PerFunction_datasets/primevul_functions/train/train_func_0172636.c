Symbol* Parser::AddDeclForPid(ParseNodePtr pnode, IdentPtr pid, SymbolType symbolType, bool errorOnRedecl, bool *isRedecl)
{
    Assert(pnode->IsVarLetOrConst());

    PidRefStack *refForUse = nullptr, *refForDecl = nullptr;

    if (isRedecl)
    {
        *isRedecl = false;
    }

    BlockInfoStack *blockInfo;
    bool fBlockScope = false;
    if (pnode->nop != knopVarDecl || symbolType == STFunction)
    {
        Assert(m_pstmtCur);
        if (m_pstmtCur->GetNop() != knopBlock)
        {

            Error(ERRDeclOutOfStmt);
        }

        if (m_pstmtCur->pstmtOuter && m_pstmtCur->pstmtOuter->GetNop() == knopSwitch)
        {

            pnode->sxVar.isSwitchStmtDecl = true;
        }

        fBlockScope = pnode->nop != knopVarDecl ||
            (
                !GetCurrentBlockInfo()->pnodeBlock->sxBlock.scope ||
                GetCurrentBlockInfo()->pnodeBlock->sxBlock.scope->GetScopeType() != ScopeType_GlobalEvalBlock
                );
    }
    if (fBlockScope)
    {
        blockInfo = GetCurrentBlockInfo();
    }
    else
    {
        blockInfo = GetCurrentFunctionBlockInfo();
    }


    if (pid == wellKnownPropertyPids.arguments
        && pnode->nop == knopVarDecl
        && blockInfo->pnodeBlock->sxBlock.blockType == PnodeBlockType::Function
        && blockInfo->pBlockInfoOuter != nullptr
        && blockInfo->pBlockInfoOuter->pnodeBlock->sxBlock.blockType == PnodeBlockType::Parameter
        && blockInfo->pnodeBlock->sxBlock.scope->GetScopeType() != ScopeType_FuncExpr
        && blockInfo->pBlockInfoOuter->pnodeBlock->sxBlock.scope->GetCanMergeWithBodyScope())
    {
        blockInfo = blockInfo->pBlockInfoOuter;
    }

    refForDecl = this->FindOrAddPidRef(pid, blockInfo->pnodeBlock->sxBlock.blockId, GetCurrentFunctionNode()->sxFnc.functionId);

    if (refForDecl == nullptr)
    {
        Error(ERRnoMemory);
    }

    if (refForDecl->funcId != GetCurrentFunctionNode()->sxFnc.functionId)
    {

        Assert(this->m_reparsingLambdaParams);
        refForDecl->funcId = GetCurrentFunctionNode()->sxFnc.functionId;
    }

    if (blockInfo == GetCurrentBlockInfo())
    {
        refForUse = refForDecl;
    }
    else
    {
        refForUse = this->PushPidRef(pid);
    }
    pnode->sxVar.symRef = refForUse->GetSymRef();
    Symbol *sym = refForDecl->GetSym();
    if (sym != nullptr)
    {
        if (isRedecl)
        {
            *isRedecl = true;
        }

        switch (pnode->nop)
        {
        case knopLetDecl:
        case knopConstDecl:
            if (!sym->GetDecl()->sxVar.isBlockScopeFncDeclVar)
            {
                Assert(errorOnRedecl);

                Error(ERRRedeclaration);
            }
            else
            {

                sym->SetSymbolType(symbolType);
                sym->SetDecl(pnode);
            }
            break;
        case knopVarDecl:
            if (m_currentScope->GetScopeType() == ScopeType_Parameter)
            {


                m_currentScope->SetHasDuplicateFormals();
            }

            if (sym->GetDecl() == nullptr)
            {
                Assert(symbolType == STFunction);
                sym->SetDecl(pnode);
                break;
            }
            switch (sym->GetDecl()->nop)
            {
            case knopLetDecl:
            case knopConstDecl:

                if (errorOnRedecl && (!IsES6DestructuringEnabled() || sym->GetSymbolType() != STFormal))
                {
                    Error(ERRRedeclaration);
                }

                break;
            case knopVarDecl:

                if (errorOnRedecl || sym->GetDecl()->sxVar.isBlockScopeFncDeclVar)
                {
                    if (symbolType == STFormal ||
                        (symbolType == STFunction && sym->GetSymbolType() != STFormal) ||
                        sym->GetSymbolType() == STVariable)
                    {

                        sym->SetSymbolType(symbolType);
                        sym->SetDecl(pnode);
                    }
                }
                break;
            }
            break;
        }
    }
    else
    {
        Scope *scope = blockInfo->pnodeBlock->sxBlock.scope;
        if (scope == nullptr)
        {
            Assert(blockInfo->pnodeBlock->sxBlock.blockType == PnodeBlockType::Regular);
            scope = Anew(&m_nodeAllocator, Scope, &m_nodeAllocator, ScopeType_Block);
            if (this->IsCurBlockInLoop())
            {
                scope->SetIsBlockInLoop();
            }
            blockInfo->pnodeBlock->sxBlock.scope = scope;
            PushScope(scope);
        }

        if (scope->GetScopeType() == ScopeType_GlobalEvalBlock)
        {
            Assert(fBlockScope);
            Assert(scope->GetEnclosingScope() == m_currentNodeProg->sxProg.scope);

            PidRefStack *pidRefOld = pid->GetPidRefForScopeId(0);
            if (pidRefOld && pidRefOld->GetSym())
            {
                Error(ERRRedeclaration);
            }
        }
        else if (scope->GetScopeType() == ScopeType_Global && (this->m_grfscr & fscrEvalCode) &&
                 !(m_functionBody && m_functionBody->GetScopeInfo()))
        {


            Assert(!fBlockScope || (this->m_grfscr & fscrConsoleScopeEval) == fscrConsoleScopeEval);
            PidRefStack *pidRefOld = pid->GetPidRefForScopeId(1);
            if (pidRefOld && pidRefOld->GetSym())
            {
                Error(ERRRedeclaration);
            }
        }

        if ((scope->GetScopeType() == ScopeType_FunctionBody || scope->GetScopeType() == ScopeType_Parameter) && symbolType != STFunction)
        {
            ParseNodePtr pnodeFnc = GetCurrentFunctionNode();
            AnalysisAssert(pnodeFnc);
            if (pnodeFnc->sxFnc.pnodeName &&
                pnodeFnc->sxFnc.pnodeName->nop == knopVarDecl &&
                pnodeFnc->sxFnc.pnodeName->sxVar.pid == pid)
            {


                m_currentNodeFunc->sxFnc.SetNameIsHidden();
            }
        }

        if (!sym)
        {
            const char16 *name = reinterpret_cast<const char16*>(pid->Psz());
            int nameLength = pid->Cch();
            SymbolName const symName(name, nameLength);

            Assert(!scope->FindLocalSymbol(symName));
            sym = Anew(&m_nodeAllocator, Symbol, symName, pnode, symbolType);
            scope->AddNewSymbol(sym);
            sym->SetPid(pid);
        }
        refForDecl->SetSym(sym);
    }
    return sym;
}
