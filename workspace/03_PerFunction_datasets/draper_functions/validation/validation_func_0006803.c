GetDefaultAmulesigPath()
{
	wxString strDir;

#ifdef __WXMAC__

	FSRef fsRef;
	if (FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &fsRef) == noErr)
	{
		CFURLRef	urlRef		= CFURLCreateFromFSRef(NULL, &fsRef);
		CFStringRef	cfString	= CFURLCopyFileSystemPath(urlRef, kCFURLPOSIXPathStyle);
		CFRelease(urlRef) ;
		#if wxCHECK_VERSION(2, 9, 0)
			strDir = wxCFStringRef(cfString).AsString(wxLocale::GetSystemEncoding())

#if 0
			+ wxFileName::GetPathSeparator() + wxT("aMule");
#else
			+ wxFileName::GetPathSeparator() + wxT(AMULE_ADUNANZA_DIR);
#endif

		#else
			strDir = wxMacCFStringHolder(cfString).AsString(wxLocale::GetSystemEncoding())

#if 0
			+ wxFileName::GetPathSeparator() + wxT("aMule");
#else
			+ wxFileName::GetPathSeparator() + wxT(AMULE_ADUNANZA_DIR);
#endif

		#endif
	}

#elif defined(__WXMSW__)

	LPITEMIDLIST pidl;

	HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);

	if (SUCCEEDED(hr)) {
		if (!SHGetPathFromIDList(pidl, wxStringBuffer(strDir, MAX_PATH))) {
			strDir = wxEmptyString;
		} else {

#if 0
			strDir = strDir + wxFileName::GetPathSeparator() + wxT("aMule");
#else
			strDir = strDir + wxFileName::GetPathSeparator() + wxT(AMULE_ADUNANZA_DIR);
#endif

		}
	}

	if (pidl) {
		LPMALLOC pMalloc;
		SHGetMalloc(&pMalloc);
		if (pMalloc) {
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
	}

#else


#if 0
	strDir = wxFileName::GetHomeDir() + wxFileName::GetPathSeparator() + wxT(".aMule");
#else
	strDir = wxFileName::GetHomeDir() + wxFileName::GetPathSeparator() + wxT(".") + wxT(AMULE_ADUNANZA_DIR);
#endif


#endif

	return strDir;
}
