CWebSock::EPageReqResult CWebSock::PrintStaticFile(const CString& sPath,
                                                   CString& sPageRet,
                                                   CModule* pModule) {
    SetPaths(pModule);
    CString sFile = m_Template.ExpandFile(sPath.TrimLeft_n("/"));
    DEBUG("About to print [" + sFile + "]");


    PrintFile(sFile);
    return PAGE_DONE;
}
