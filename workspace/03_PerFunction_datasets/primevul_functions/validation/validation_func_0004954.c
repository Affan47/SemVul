CWebSock::~CWebSock() {
    if (m_spAuth) {
        m_spAuth->Invalidate();
    }


    CUser* pUser = GetSession()->GetUser();
    if (pUser) {
        pUser->AddBytesWritten(GetBytesWritten());
        pUser->AddBytesRead(GetBytesRead());
    } else {
        CZNC::Get().AddBytesWritten(GetBytesWritten());
        CZNC::Get().AddBytesRead(GetBytesRead());
    }


    ResetBytesWritten();
    ResetBytesRead();
}
