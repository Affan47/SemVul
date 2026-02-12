void CWebSock::OnPageRequest(const CString& sURI) {
    CString sPageRet;
    EPageReqResult eRet = OnPageRequestInternal(sURI, sPageRet);
    switch (eRet) {
        case PAGE_PRINT:
            PrintPage(sPageRet);
            break;
        case PAGE_DEFERRED:

            break;
        case PAGE_DONE:


            Close(CLT_AFTERWRITE);
            break;
        case PAGE_NOTFOUND:
        default:
            PrintNotFound();
            break;
    }
}
