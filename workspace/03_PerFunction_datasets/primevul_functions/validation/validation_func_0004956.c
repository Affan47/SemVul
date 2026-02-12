VCString CWebSock::GetDirs(CModule* pModule, bool bIsTemplate) {
    CString sHomeSkinsDir(CZNC::Get().GetZNCPath() + "/webskins/");
    CString sSkinName(GetSkinName());
    VCString vsResult;


    if (pModule) {
        const CString& sModName(pModule->GetModName());


        if (!sSkinName.empty()) {
            vsResult.push_back(GetSkinPath(sSkinName) + "/mods/" + sModName +
                               "/");
        }


        vsResult.push_back(GetSkinPath("_default_") + "/mods/" + sModName +
                           "/");


        vsResult.push_back(pModule->GetModDataDir() + "/tmpl/");


        if (!sSkinName.empty()) {
            vsResult.push_back(GetSkinPath(sSkinName) + "/mods/" + sModName +
                               "/");
        }


        vsResult.push_back(GetSkinPath("_default_") + "/mods/" + sModName +
                           "/");
    }


    if (!sSkinName.empty()) {
        vsResult.push_back(GetSkinPath(sSkinName) +
                           CString(bIsTemplate ? "/tmpl/" : "/"));
    }


    vsResult.push_back(GetSkinPath("_default_") +
                       CString(bIsTemplate ? "/tmpl/" : "/"));

    return vsResult;
}
