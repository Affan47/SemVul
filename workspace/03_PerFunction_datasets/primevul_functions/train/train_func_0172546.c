uint Parser::CalculateFunctionColumnNumber()
{
    uint columnNumber;

    if (m_pscan->IchMinTok() >= m_pscan->IchMinLine())
    {

        columnNumber = m_pscan->IchMinTok() - m_pscan->IchMinLine();
        if (m_functionBody != nullptr && m_functionBody->GetRelativeLineNumber() == m_pscan->LineCur())
        {

            columnNumber += m_functionBody->GetRelativeColumnNumber();
        }
    }
    else if (m_currentNodeFunc)
    {


        ULONG offsetFromCurrentFunction = m_pscan->IchMinTok() - m_currentNodeFunc->ichMin;
        columnNumber = m_currentNodeFunc->sxFnc.columnNumber + offsetFromCurrentFunction ;
    }
    else
    {

        columnNumber = 0;
    }

    return columnNumber;
}
