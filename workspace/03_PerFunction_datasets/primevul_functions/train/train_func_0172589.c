ParseNodePtr Parser::ParseDefaultExportClause()
{
    Assert(m_token.tk == tkDEFAULT);

    m_pscan->Scan();
    ParseNodePtr pnode = nullptr;
    ushort flags = fFncNoFlgs;

    switch (m_token.tk)
    {
    case tkCLASS:
        {
            if (!m_scriptContext->GetConfig()->IsES6ClassAndExtendsEnabled())
            {
                goto LDefault;
            }


            BOOL classHasName = false;
            RestorePoint parsedClass;
            m_pscan->Capture(&parsedClass);
            m_pscan->Scan();

            if (m_token.tk == tkID)
            {
                classHasName = true;
            }

            m_pscan->SeekTo(parsedClass);
            pnode = ParseClassDecl<buildAST>(classHasName, nullptr, nullptr, nullptr);

            if (buildAST)
            {
                AnalysisAssert(pnode != nullptr);
                Assert(pnode->nop == knopClassDecl);

                pnode->sxClass.SetIsDefaultModuleExport(true);
            }

            break;
        }
    case tkID:


        if (wellKnownPropertyPids.async == m_token.GetIdentifier(m_phtbl))
        {
            RestorePoint parsedAsync;
            m_pscan->Capture(&parsedAsync);
            m_pscan->Scan();
            if (m_token.tk == tkFUNCTION)
            {


                flags |= fFncAsync;
                goto LFunction;
            }


            m_pscan->SeekTo(parsedAsync);
        }
        goto LDefault;
        break;
    case tkFUNCTION:
        {
LFunction:


            RestorePoint parsedFunction;
            m_pscan->Capture(&parsedFunction);
            m_pscan->Scan();

            if (m_token.tk == tkStar)
            {


                m_pscan->Scan();
            }


            if (m_token.tk == tkID)
            {
                flags |= fFncDeclaration;
            }
            else
            {
                flags |= fFncNoName;
            }


            m_pscan->SeekTo(parsedFunction);
            pnode = ParseFncDecl<buildAST>(flags);

            if (buildAST)
            {
                AnalysisAssert(pnode != nullptr);
                Assert(pnode->nop == knopFncDecl);

                pnode->sxFnc.SetIsDefaultModuleExport(true);
            }
            break;
        }
    default:
LDefault:
        {
            ParseNodePtr pnodeExpression = ParseExpr<buildAST>();


            if (pnodeExpression && pnodeExpression->nop == knopComma)
            {
                Error(ERRsyntax);
            }

            if (buildAST)
            {
                AnalysisAssert(pnodeExpression != nullptr);


                pnode = CreateNode(knopExportDefault);
                pnode->sxExportDefault.pnodeExpr = pnodeExpression;
            }
            break;
        }
    }

    IdentPtr exportName = wellKnownPropertyPids._default;
    IdentPtr localName = wellKnownPropertyPids._starDefaultStar;
    AddModuleImportOrExportEntry(EnsureModuleLocalExportEntryList(), nullptr, localName, exportName, nullptr);

    return pnode;
}
