CString SafeGetUserNameParam(CWebSock& WebSock) {
		CString sUserName = WebSock.GetParam("user");
		if(sUserName.empty() && !WebSock.IsPost()) {


			sUserName = WebSock.GetParam("user", false);
		}
		return sUserName;
	}
