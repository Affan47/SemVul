bool WindowsServiceControl::setStartType( int startType )
{
	if( checkService() == false || startType == InvalidStartType )
	{
		return false;
	}

	if( ChangeServiceConfig( m_serviceHandle,
							 SERVICE_NO_CHANGE,
							 static_cast<DWORD>( startType ),
							 SERVICE_NO_CHANGE,
							 nullptr,
							 nullptr,
							 nullptr,
							 nullptr,
							 nullptr,
							 nullptr,
							 nullptr
							 ) == false )
	{
		vCritical() << qUtf8Printable( tr( "The start type of service \"%1\" could not be changed." ).arg( m_name ) );
		return false;
	}

	return true;
}
