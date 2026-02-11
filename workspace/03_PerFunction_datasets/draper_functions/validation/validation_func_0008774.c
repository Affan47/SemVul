getRecvBuff()
	{
		int val;
		socklen_t size=sizeof(val);
		if(getsockopt(m_Socket,SOL_SOCKET,SO_RCVBUF,(char*)&val,&size)==SOCKET_ERROR)
			return E_UNKNOWN;
		else
			return val;
	}
