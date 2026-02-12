ParseNodePtr Parser::ParseImportDeclaration()
{
    Assert(m_scriptContext->GetConfig()->IsES6ModuleEnabled());
    Assert(m_token.tk == tkIMPORT);

    if (!IsImportOrExportStatementValidHere())
    {
        Error(ERRInvalidModuleImportOrExport);
    }


    m_pscan->Scan();

    if (m_token.tk == tkStrCon)
    {


        if (buildAST)
        {
            AddModuleSpecifier(m_token.GetStr());
        }


        m_pscan->Scan();
    }
    else
    {
        ModuleImportOrExportEntryList importEntryList(&m_nodeAllocator);


        ParseImportClause<buildAST>(&importEntryList);


        IdentPtr moduleSpecifier = ParseImportOrExportFromClause<buildAST>(true);

        if (buildAST)
        {
            Assert(moduleSpecifier != nullptr);

            AddModuleSpecifier(moduleSpecifier);

            importEntryList.Map([this, moduleSpecifier](ModuleImportOrExportEntry& importEntry) {
                importEntry.moduleRequest = moduleSpecifier;
                AddModuleImportOrExportEntry(EnsureModuleImportEntryList(), &importEntry);
            });
        }

        importEntryList.Clear();
    }


    return nullptr;
}
