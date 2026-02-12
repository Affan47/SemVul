DNSRequest* DNS::AddQuery(DNSHeader *header, int &id, const char* original)
{

	if (this->GetFd() == -1)
		return NULL;


	unsigned int tries = 0;
	do {
		id = ServerInstance->GenRandomInt(DNS::MAX_REQUEST_ID);
		if (++tries == DNS::MAX_REQUEST_ID*5)
		{


			id = -1;
			for (int i = 0; i < DNS::MAX_REQUEST_ID; i++)
			{
				if (!requests[i])
				{
					id = i;
					break;
				}
			}

			if (id == -1)
				throw ModuleException("DNS: All ids are in use");

			break;
		}
	} while (requests[id]);

	DNSRequest* req = new DNSRequest(this, id, original);

	header->id[0] = req->id[0] = id >> 8;
	header->id[1] = req->id[1] = id & 0xFF;
	header->flags1 = FLAGS_MASK_RD;
	header->flags2 = 0;
	header->qdcount = 1;
	header->ancount = 0;
	header->nscount = 0;
	header->arcount = 0;


	requests[id] = req;


	return req;
}
