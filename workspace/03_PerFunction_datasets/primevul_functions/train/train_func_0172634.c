void Parser::ParseNamedImportOrExportClause(ModuleImportOrExportEntryList* importOrExportEntryList, bool isExportClause)
{
    Assert(m_token.tk == tkLCurly);
    Assert(importOrExportEntryList != nullptr);

    m_pscan->Scan();

    while (m_token.tk != tkRCurly && m_token.tk != tkEOF)
    {
        tokens firstToken = m_token.tk;

        if (!(m_token.IsIdentifier() || m_token.IsReservedWord()))
        {
            Error(ERRsyntax);
        }

        IdentPtr identifierName = m_token.GetIdentifier(m_phtbl);
        IdentPtr identifierAs = identifierName;

        m_pscan->Scan();

        if (m_token.tk == tkID)
        {

            if (wellKnownPropertyPids.as != m_token.GetIdentifier(m_phtbl))
            {
                Error(ERRsyntax);
            }

            m_pscan->Scan();


            if (!isExportClause)
            {
                ChkCurTokNoScan(tkID, ERRsyntax);
            }

            if (!(m_token.IsIdentifier() || m_token.IsReservedWord()))
            {
                Error(ERRsyntax);
            }

            identifierAs = m_token.GetIdentifier(m_phtbl);


            m_pscan->Scan();
        }
        else if (!isExportClause && firstToken != tkID)
        {


            Error(ERRsyntax);
        }

        if (m_token.tk == tkComma)
        {

            m_pscan->Scan();
        }

        if (buildAST)
        {

            if (!isExportClause)
            {
                CreateModuleImportDeclNode(identifierAs);
                AddModuleImportOrExportEntry(importOrExportEntryList, identifierName, identifierAs, nullptr, nullptr);
            }
            else
            {
                identifierName->SetIsModuleExport();
                AddModuleImportOrExportEntry(importOrExportEntryList, nullptr, identifierName, identifierAs, nullptr);
            }
        }
    }


    ChkCurTokNoScan(tkRCurly, ERRsyntax);
}
