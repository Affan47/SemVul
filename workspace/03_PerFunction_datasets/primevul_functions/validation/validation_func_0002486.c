bool CClient::OnCTCPMessage(CCTCPMessage& Message) {
    CString sTargets = Message.GetTarget();

    VCString vTargets;
    sTargets.Split(",", vTargets, false);

    if (Message.IsReply()) {
        CString sCTCP = Message.GetText();
        if (sCTCP.Token(0) == "VERSION") {


            Message.SetText(sCTCP + " via " + CZNC::GetTag(false));
        }
    }

    for (CString& sTarget : vTargets) {
        Message.SetTarget(sTarget);
        if (m_pNetwork) {

            Message.SetChan(m_pNetwork->FindChan(sTarget));
        }

        bool bContinue = false;
        if (Message.IsReply()) {
            NETWORKMODULECALL(OnUserCTCPReplyMessage(Message), m_pUser,
                              m_pNetwork, this, &bContinue);
        } else {
            NETWORKMODULECALL(OnUserCTCPMessage(Message), m_pUser, m_pNetwork,
                              this, &bContinue);
        }
        if (bContinue) continue;

        if (!GetIRCSock()) {

            if (!sTarget.Equals(m_sNick))
                PutStatus(t_f(
                    "Your CTCP to {1} got lost, you are not connected to IRC!")(
                    Message.GetTarget()));
            continue;
        }

        if (m_pNetwork) {
            PutIRC(Message.ToString(CMessage::ExcludePrefix |
                                    CMessage::ExcludeTags));
        }
    }

    return true;
}
