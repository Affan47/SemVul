DNSResult DNS::GetResult()
{

	DNSHeader header;
	DNSRequest *req;
	unsigned char buffer[sizeof(DNSHeader)];
	irc::sockets::sockaddrs from;
	memset(&from, 0, sizeof(from));
	socklen_t x = sizeof(from);

	int length = ServerInstance->SE->RecvFrom(this, (char*)buffer, sizeof(DNSHeader), 0, &from.sa, &x);


	if (length < 12)
	{
		ServerInstance->Logs->Log("RESOLVER",DEBUG,"GetResult didn't get a full packet (len=%d)", length);

		return DNSResult(-1,"",0,"");
	}


	if (from != myserver)
	{
		ServerInstance->Logs->Log("RESOLVER",DEBUG,"Got a result from the wrong server! Bad NAT or DNS forging attempt? '%s' != '%s'",
			from.str().c_str(), myserver.str().c_str());
		return DNSResult(-1,"",0,"");
	}


	DNS::FillHeader(&header,buffer,length - 12);


	unsigned long this_id = header.id[1] + (header.id[0] << 8);


	if (!requests[this_id])
	{

		ServerInstance->Logs->Log("RESOLVER",DEBUG,"Hmm, got a result that we didn't ask for (id=%lx). Ignoring.", this_id);
		return DNSResult(-1,"",0,"");
	}
	else
	{

		req = requests[this_id];
		requests[this_id] = NULL;
	}


	DNSInfo data = req->ResultIsReady(header, length);
	std::string resultstr;


	if (data.first == NULL)
	{


		std::string ro = req->orig;
		delete req;
		return DNSResult(this_id | ERROR_MASK, data.second, 0, ro);
	}
	else
	{
		unsigned long ttl = req->ttl;
		char formatted[128];


		switch (req->type)
		{
			case DNS_QUERY_A:
				snprintf(formatted,16,"%u.%u.%u.%u",data.first[0],data.first[1],data.first[2],data.first[3]);
				resultstr = formatted;
			break;

			case DNS_QUERY_AAAA:
			{
				inet_ntop(AF_INET6, data.first, formatted, sizeof(formatted));
				char* c = strstr(formatted,":0:");
				if (c != NULL)
				{
					memmove(c+1,c+2,strlen(c+2) + 1);
					c += 2;
					while (memcmp(c,"0:",2) == 0)
						memmove(c,c+2,strlen(c+2) + 1);
					if (memcmp(c,"0",2) == 0)
						*c = 0;
					if (memcmp(formatted,"0::",3) == 0)
						memmove(formatted,formatted + 1, strlen(formatted + 1) + 1);
				}
				resultstr = formatted;


				if (*formatted == ':')
					resultstr.insert(0, "0");
			}
			break;

			case DNS_QUERY_CNAME:


			case DNS_QUERY_PTR:

				resultstr = std::string((const char*)data.first);
			break;

			default:
			break;
		}


		std::string ro = req->orig;
		delete req;
		return DNSResult(this_id,resultstr,ttl,ro);
	}
}
