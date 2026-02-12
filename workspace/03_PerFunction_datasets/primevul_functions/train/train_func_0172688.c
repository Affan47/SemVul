void Parser::PrepareScanner(bool fromExternal)
{


    if (nullptr == (m_phtbl = HashTbl::Create(HASH_TABLE_SIZE, &m_err)))
        Error(ERRnoMemory);
    InitPids();


    if (nullptr == (m_pscan = Scanner_t::Create(this, m_phtbl, &m_token, &m_err, m_scriptContext)))
        Error(ERRnoMemory);

    if (fromExternal)
        m_pscan->FromExternalSource();
}
