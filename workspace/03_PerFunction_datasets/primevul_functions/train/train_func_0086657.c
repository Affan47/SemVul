bool DNS::AddResolverClass(Resolver* r)
{
	ServerInstance->Logs->Log("RESOLVER",DEBUG,"AddResolverClass 0x%08lx", (unsigned long)r);

	if ((r) && (r->GetId() > -1))
	{


		if (!Classes[r->GetId()])
		{

			Classes[r->GetId()] = r;
			return true;
		}
		else

			return false;
	}
	else
	{


		if (r)
			delete r;

		return false;
	}
}
