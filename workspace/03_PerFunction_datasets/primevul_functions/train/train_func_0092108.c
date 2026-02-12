EResult CSteamNetworkConnectionUDP::AcceptConnection( SteamNetworkingMicroseconds usecNow )
{
	if ( !Transport() )
	{
		AssertMsg( false, "Cannot acception UDP connection.  No transport?" );
		return k_EResultFail;
	}


	Transport()->SendConnectOK( usecNow );


	ConnectionState_Connected( usecNow );


	return k_EResultOK;
}
