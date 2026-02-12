void Parser::ParseImportClause(ModuleImportOrExportEntryList* importEntryList, bool parsingAfterComma)
{
    bool parsedNamespaceOrNamedImport = false;

    switch (m_token.tk)
    {
    case tkID:


        if (parsingAfterComma)
        {
            Error(ERRsyntax);
        }

        if (buildAST)
        {
            IdentPtr localName = m_token.GetIdentifier(m_phtbl);
            IdentPtr importName = wellKnownPropertyPids._default;

            CreateModuleImportDeclNode(localName);
            AddModuleImportOrExportEntry(importEntryList, importName, localName, nullptr, nullptr);
        }

        break;

    case tkLCurly:

        ParseNamedImportOrExportClause<buildAST>(importEntryList, false);

        parsedNamespaceOrNamedImport = true;
        break;

    case tkStar:


        m_pscan->Scan();
        if (m_token.tk != tkID || wellKnownPropertyPids.as != m_token.GetIdentifier(m_phtbl))
        {
            Error(ERRsyntax);
        }


        m_pscan->Scan();
        ChkCurTokNoScan(tkID, ERRsyntax);

        if (buildAST)
        {
            IdentPtr localName = m_token.GetIdentifier(m_phtbl);
            IdentPtr importName = wellKnownPropertyPids._star;

            CreateModuleImportDeclNode(localName);
            AddModuleImportOrExportEntry(importEntryList, importName, localName, nullptr, nullptr);
        }

        parsedNamespaceOrNamedImport = true;
        break;

    default:
        Error(ERRsyntax);
    }

    m_pscan->Scan();

    if (m_token.tk == tkComma)
    {


        if (parsingAfterComma || parsedNamespaceOrNamedImport)
        {
            Error(ERRsyntax);
        }

        m_pscan->Scan();

        ParseImportClause<buildAST>(importEntryList, true);
    }
}
