void Parser::ValidateFormals()
{
    ParseFncFormals<false>(nullptr, nullptr, fFncNoFlgs);

    m_pscan->Scan();
}
