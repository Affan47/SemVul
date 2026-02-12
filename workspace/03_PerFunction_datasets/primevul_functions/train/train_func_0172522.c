void Parser::FinishDeferredFunction(ParseNodePtr pnodeScopeList)
{
    VisitFunctionsInScope(pnodeScopeList,
        [this](ParseNodePtr pnodeFnc)
    {
        Assert(pnodeFnc->nop == knopFncDecl);


        if (pnodeFnc->sxFnc.pnodeBody == nullptr && !pnodeFnc->sxFnc.HasNonSimpleParameterList())
        {

            JS_ETW_INTERNAL(EventWriteJSCRIPT_PARSE_FUNC(this->GetScriptContext(), pnodeFnc->sxFnc.functionId, TRUE));

            ParseNodePtr pnodeFncSave = this->m_currentNodeFunc;
            this->m_currentNodeFunc = pnodeFnc;

            ParseNodePtr pnodeFncExprBlock = nullptr;
            if (pnodeFnc->sxFnc.pnodeName &&
                !pnodeFnc->sxFnc.IsDeclaration())
            {

                ParseNodePtr pnodeName = pnodeFnc->sxFnc.pnodeName;
                Assert(pnodeName->nop == knopVarDecl);
                Assert(pnodeName->sxVar.pnodeNext == nullptr);

                pnodeFncExprBlock = this->StartParseBlock<true>(PnodeBlockType::Function, ScopeType_FuncExpr);
                PidRefStack *ref = this->PushPidRef(pnodeName->sxVar.pid);
                pnodeName->sxVar.symRef = ref->GetSymRef();
                ref->SetSym(pnodeName->sxVar.sym);

                Scope *fncExprScope = pnodeFncExprBlock->sxBlock.scope;
                fncExprScope->AddNewSymbol(pnodeName->sxVar.sym);
                pnodeFnc->sxFnc.scope = fncExprScope;
            }

            ParseNodePtr pnodeBlock = this->StartParseBlock<true>(PnodeBlockType::Parameter, ScopeType_Parameter);
            pnodeFnc->sxFnc.pnodeScopes = pnodeBlock;
            m_ppnodeScope = &pnodeBlock->sxBlock.pnodeScopes;
            pnodeBlock->sxBlock.pnodeStmt = pnodeFnc;


            Scope *scope = pnodeBlock->sxBlock.scope;
            auto addArgsToScope = [&](ParseNodePtr pnodeArg) {
                if (pnodeArg->IsVarLetOrConst())
                {
                    PidRefStack *ref = this->PushPidRef(pnodeArg->sxVar.pid);
                    pnodeArg->sxVar.symRef = ref->GetSymRef();
                    if (ref->GetSym() != nullptr)
                    {


                        Assert(ref->GetSym() == pnodeArg->sxVar.sym);
                        ref->GetSym()->SetDecl(pnodeArg);
                    }
                    else
                    {
                        ref->SetSym(pnodeArg->sxVar.sym);
                        scope->AddNewSymbol(pnodeArg->sxVar.sym);
                    }
                }
            };
            MapFormals(pnodeFnc, addArgsToScope);
            MapFormalsFromPattern(pnodeFnc, addArgsToScope);

            ParseNodePtr pnodeInnerBlock = this->StartParseBlock<true>(PnodeBlockType::Function, ScopeType_FunctionBody);
            pnodeFnc->sxFnc.pnodeBodyScope = pnodeInnerBlock;


            *m_ppnodeScope = pnodeInnerBlock;

            ParseNodePtr *ppnodeScopeSave = nullptr;
            ParseNodePtr *ppnodeExprScopeSave = nullptr;

            ppnodeScopeSave = m_ppnodeScope;


            m_ppnodeScope = &pnodeInnerBlock->sxBlock.pnodeScopes;
            pnodeInnerBlock->sxBlock.pnodeStmt = pnodeFnc;


            ppnodeExprScopeSave = m_ppnodeExprScope;
            m_ppnodeExprScope = nullptr;


            Assert(*m_ppnodeVar == nullptr);


            pnodeFnc->sxFnc.pnodeVars = nullptr;
            m_ppnodeVar = &pnodeFnc->sxFnc.pnodeVars;

            if (scope != nullptr && !pnodeFnc->sxFnc.IsAsync())
            {
                if (scope->GetCanMergeWithBodyScope())
                {
                    scope->ForEachSymbol([this](Symbol* paramSym)
                    {
                        PidRefStack* ref = PushPidRef(paramSym->GetPid());
                        ref->SetSym(paramSym);
                    });
                }
                else
                {
                    OUTPUT_TRACE_DEBUGONLY(Js::ParsePhase, _u("The param and body scope of the function %s cannot be merged\n"), pnodeFnc->sxFnc.pnodeName ? pnodeFnc->sxFnc.pnodeName->sxVar.pid->Psz() : _u("Anonymous function"));

                    scope->ForEachSymbol([this](Symbol* param) {
                        OUTPUT_TRACE_DEBUGONLY(Js::ParsePhase, _u("Creating a duplicate symbol for the parameter %s in the body scope\n"), param->GetPid()->Psz());
                        ParseNodePtr paramNode = this->CreateVarDeclNode(param->GetPid(), STVariable, false, nullptr, false);
                        Assert(paramNode && paramNode->sxVar.sym->GetScope()->GetScopeType() == ScopeType_FunctionBody);
                        paramNode->sxVar.sym->SetHasInit(true);
                    });
                }
            }

            Assert(m_currentNodeNonLambdaFunc == nullptr);
            m_currentNodeNonLambdaFunc = pnodeFnc;

            this->FinishFncNode(pnodeFnc);

            Assert(pnodeFnc == m_currentNodeNonLambdaFunc);
            m_currentNodeNonLambdaFunc = nullptr;

            m_ppnodeExprScope = ppnodeExprScopeSave;

            AssertMem(m_ppnodeScope);
            Assert(nullptr == *m_ppnodeScope);
            m_ppnodeScope = ppnodeScopeSave;

            this->FinishParseBlock(pnodeInnerBlock);

            this->AddArgumentsNodeToVars(pnodeFnc);

            this->FinishParseBlock(pnodeBlock);
            if (pnodeFncExprBlock)
            {
                this->FinishParseBlock(pnodeFncExprBlock);
            }

            this->m_currentNodeFunc = pnodeFncSave;
        }
    });
}
