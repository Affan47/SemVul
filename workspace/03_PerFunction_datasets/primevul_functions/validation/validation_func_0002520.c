void CClient::AcceptLogin(CUser& User) {
    m_sPass = "";
    m_pUser = &User;


    SetTimeout(User.GetNoTrafficTimeout(), TMO_READ);

    SetSockName("USR::" + m_pUser->GetUsername());
    SetEncoding(m_pUser->GetClientEncoding());

    if (!m_sNetwork.empty()) {
        m_pNetwork = m_pUser->FindNetwork(m_sNetwork);
        if (!m_pNetwork) {
            PutStatus(t_f("Network {1} doesn't exist.")(m_sNetwork));
        }
    } else if (!m_pUser->GetNetworks().empty()) {


        m_pNetwork = m_pUser->FindNetwork("default");


        if (!m_pNetwork) m_pNetwork = m_pUser->FindNetwork("user");

        if (!m_pNetwork) m_pNetwork = *m_pUser->GetNetworks().begin();
        if (m_pNetwork && m_pUser->GetNetworks().size() > 1) {
            PutStatusNotice(
                t_s("You have several networks configured, but no network was "
                    "specified for the connection."));
            PutStatusNotice(
                t_f("Selecting network {1}. To see list of all configured "
                    "networks, use /znc ListNetworks")(m_pNetwork->GetName()));
            PutStatusNotice(t_f(
                "If you want to choose another network, use /znc JumpNetwork "
                "<network>, or connect to ZNC with username {1}/<network> "
                "(instead of just {1})")(m_pUser->GetUsername()));
        }
    } else {
        PutStatusNotice(
            t_s("You have no networks configured. Use /znc AddNetwork "
                "<network> to add one."));
    }

    SetNetwork(m_pNetwork, false);

    SendMotd();

    NETWORKMODULECALL(OnClientLogin(), m_pUser, m_pNetwork, this, NOTHING);
}
