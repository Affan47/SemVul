DNS::DNS()
{
	ServerInstance->Logs->Log("RESOLVER",DEBUG,"DNS::DNS");

	memset(Classes,0,sizeof(Classes));


	memset(requests,0,sizeof(requests));


	this->cache = NULL;


	this->SetFd(-1);


	this->Rehash();

	this->PruneTimer = new CacheTimer(this);

	ServerInstance->Timers->AddTimer(this->PruneTimer);
}
