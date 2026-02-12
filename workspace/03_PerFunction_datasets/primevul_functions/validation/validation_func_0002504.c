void CAuthBase::RefuseLogin(const CString& sReason) {
    if (!m_pSock) return;

    CUser* pUser = CZNC::Get().FindUser(GetUsername());


    if (pUser) {
        pUser->PutStatusNotice(t_f(
            "A client from {1} attempted to login as you, but was rejected: "
            "{2}")(GetRemoteIP(), sReason));
    }

    GLOBALMODULECALL(OnFailedLogin(GetUsername(), GetRemoteIP()), NOTHING);
    RefusedLogin(sReason);
    Invalidate();
}
