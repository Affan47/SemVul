bool CClient::OnModeMessage(CModeMessage& Message) {
    CString sTarget = Message.GetTarget();

    if (m_pNetwork && m_pNetwork->IsChan(sTarget) && !Message.HasModes()) {


        CChan* pChan = m_pNetwork->FindChan(sTarget);
        if (pChan && pChan->IsOn() && !pChan->GetModeString().empty()) {
            PutClient(":" + m_pNetwork->GetIRCServer() + " 324 " + GetNick() +
                      " " + sTarget + " " + pChan->GetModeString());
            if (pChan->GetCreationDate() > 0) {
                PutClient(":" + m_pNetwork->GetIRCServer() + " 329 " +
                          GetNick() + " " + sTarget + " " +
                          CString(pChan->GetCreationDate()));
            }
            return true;
        }
    }

    return false;
}
