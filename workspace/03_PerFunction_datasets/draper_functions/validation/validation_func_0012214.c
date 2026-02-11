gf_mkdir(char* DirPathName)
{
#if defined (_WIN32_WCE)
	TCHAR swzName[MAX_PATH];
	BOOL res;
	CE_CharToWide(DirPathName, swzName);
	res = CreateDirectory(swzName, NULL);
	if (! res) {
		int err = GetLastError();
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot create director %s: last error %d\n", DirPathName, err ));
	}
#elif defined (WIN32)
	int res = mkdir(DirPathName);
	if (res==-1) {
		int err = GetLastError();
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot create director %s: last error %d\n", DirPathName, err ));
	}
#else
    int res = mkdir(DirPathName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (res==-1) {
		if(errno == 17){
			GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot create director %s, it already exists: last error %d \n", DirPathName, errno ));
			return GF_BAD_PARAM;
		}else{
			GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot create director %s: last error %d\n", DirPathName, errno ));
			return GF_IO_ERR;
		}
	}
#endif
	return GF_OK;
}
