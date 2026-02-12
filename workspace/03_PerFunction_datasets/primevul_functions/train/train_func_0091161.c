void DNS::HandleEvent(EventType, int)
{

	DNSResult res(0,"",0,"");
	res.id = 0;
	ServerInstance->Logs->Log("RESOLVER",DEBUG,"Handle DNS event");

	res = this->GetResult();

	ServerInstance->Logs->Log("RESOLVER",DEBUG,"Result id %d", res.id);


	if (res.id != -1)
	{

		if (res.id & ERROR_MASK)
		{

			res.id -= ERROR_MASK;

			if (Classes[res.id])
			{
				if (ServerInstance && ServerInstance->stats)
					ServerInstance->stats->statsDnsBad++;
				Classes[res.id]->OnError(RESOLVER_NXDOMAIN, res.result);
				delete Classes[res.id];
				Classes[res.id] = NULL;
			}
			return;
		}
		else
		{

			if (Classes[res.id])
			{
				if (ServerInstance && ServerInstance->stats)
					ServerInstance->stats->statsDnsGood++;

				if (!this->GetCache(res.original.c_str()))
					this->cache->insert(std::make_pair(res.original.c_str(), CachedQuery(res.result, res.type, res.ttl)));

				Classes[res.id]->OnLookupComplete(res.result, res.ttl, false);
				delete Classes[res.id];
				Classes[res.id] = NULL;
			}
		}

		if (ServerInstance && ServerInstance->stats)
			ServerInstance->stats->statsDns++;
	}
}
