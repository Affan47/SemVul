GetKadStatus()
{
	if ( theApp->IsConnectedKad() ) {
		return 1;
	} else if ( Kademlia::CKademlia::IsFirewalled() ) {
		return 2;
	} else if ( Kademlia::CKademlia::IsRunning() ) {
		return 3;
	}
	return 0;
}
