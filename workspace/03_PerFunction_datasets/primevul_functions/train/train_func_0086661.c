DNSRequest* DNS::AddQuery(DNSHeader *header, int &id, const char* original)
{

	if (this->GetFd() == -1)
		return NULL;


	do {
		id = ServerInstance->GenRandomInt(DNS::MAX_REQUEST_ID);
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
