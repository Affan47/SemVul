CString SafeGetNetworkParam(CWebSock& WebSock) {
		CString sNetwork = WebSock.GetParam("network");
		if(sNetwork.empty() && !WebSock.IsPost()) {


			sNetwork = WebSock.GetParam("network", false);
		}
		return sNetwork;
	}
