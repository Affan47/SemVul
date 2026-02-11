send(const UINT8* buff,UINT32 len)
	{
	  if(len==0)
			return 0;
		int ret;
		SINT32 ef=0;
		do
			{
				ret=::send(m_Socket,(char*)buff,len,MSG_NOSIGNAL);
				#ifdef _DEBUG
					if(ret==SOCKET_ERROR)
						CAMsg::printMsg(LOG_DEBUG,"Fehler beim Socket-send: %i\n",GET_NET_ERROR);
				#endif
			}
		while(ret==SOCKET_ERROR&&(ef=GET_NET_ERROR)==EINTR);
		if(ret==SOCKET_ERROR)
			{
				if(ef==ERR_INTERN_WOULDBLOCK)
					{
						#ifdef _DEBUG
							CAMsg::printMsg(LOG_DEBUG,"Fehler beim Socket-send: E_AGAIN\n");
						#endif
						return E_AGAIN;
					}
				#ifdef _DEBUG
					CAMsg::printMsg(LOG_DEBUG,"Fehler beim Socket-send:E_UNKNOWN (ef=%i)\n",ef);
				#endif
				return E_UNKNOWN;
			}
	  return ret;
	}
