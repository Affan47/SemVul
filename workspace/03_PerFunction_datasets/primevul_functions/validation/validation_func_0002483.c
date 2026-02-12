bool CClient::OnQuitMessage(CQuitMessage& Message) {
    bool bReturn = false;
    NETWORKMODULECALL(OnUserQuitMessage(Message), m_pUser, m_pNetwork, this,
                      &bReturn);
    if (!bReturn) {
        Close(Csock::CLT_AFTERWRITE);
    }


    return true;
}
