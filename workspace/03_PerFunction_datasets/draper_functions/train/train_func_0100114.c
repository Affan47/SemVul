parseHTTPHeader(UINT32* contentLength, UINT32 * statusCode, UINT32 msTimeOut)
	{
		if(contentLength!=NULL)
			*contentLength=0;
		if(statusCode!=NULL)
			*statusCode=0;
		char *line = new char[255];
		SINT32 ret = 0;
		SINT32 ret2 = E_UNKNOWN;

		UINT64 currentTime = 0, endTime = 0;
		bool nbl = false;

		getcurrentTimeMillis(currentTime);
		set64(endTime,currentTime);
		add64(endTime,msTimeOut);

		if(msTimeOut > 0)
		{
			m_pSocket->getNonBlocking(&nbl);
			m_pSocket->setNonBlocking(true);
		}

		if(!m_pSocket)
		{
			return E_NOT_CONNECTED;
		}
		do
		{
			int i=0;
			UINT8 byte = 0;
			do
			{

receiving:
				ret = m_pSocket->receive(&byte, 1);
				if( (ret == E_AGAIN) && (msTimeOut > 0) )
				{
					getcurrentTimeMillis(currentTime);
					if(!isLesser64(currentTime,endTime))
					{
						CAMsg::printMsg(LOG_ERR, "HTTP-Client parseHeader: timeout!\n");
						ret = E_TIMEDOUT;
						ret2 = E_TIMEDOUT;
						break;
					}
					msTimeOut=diff64(endTime,currentTime);
					msSleep(50);
					goto receiving;
				}
				if(byte == '\r' || byte == '\n')
				{
					line[i++] = 0;
				}
				else
				{
					line[i++] = byte;
				}
			}
			while(byte != '\n' && i<255 && ret > 0 );

			if(ret < 0||i>=255)
			{
				CAMsg::printMsg(LOG_CRIT,"HttpClient: Error return code: %i.\n",ret);
				break;
			}
			if(strncmp(line, "HTTP", 4) == 0)
				{
					if(statusCode!=NULL && strlen(line)>9)
						{
							*statusCode = atoi(line+9);
						}
					if(strstr(line, "200 OK") == NULL)
						{
							CAMsg::printMsg(LOG_CRIT,"HttpClient: Error: Server returned: '%s'.\n",line);
							break;
						}
					else
						ret2=E_SUCCESS;
				}

			else if( (strncmp(line, "Content-length: ", 16) == 0) ||
									(strncmp(line, "Content-Length: ", 16) == 0))
				{
					*contentLength = (UINT32) atol(line+16);
				}
			#ifdef DEBUG
				CAMsg::printMsg(LOG_DEBUG,"Server returned: '%s'.\n",line);
			#endif
		}
		while(strlen(line) > 0);
		if(msTimeOut > 0)
		{
			m_pSocket->setNonBlocking(nbl);
		}
		delete[] line;
		line = NULL;
		return ret2;
	}
