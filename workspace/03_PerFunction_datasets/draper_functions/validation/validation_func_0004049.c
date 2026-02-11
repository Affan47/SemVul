OnAttach(void)
{
	Clear();

	if (rakPeerInterface->IsActive())
		startupTime=RakNet::GetTimeUS();
}
