sendConnectionName( QString name )
{
	init( (uchar) SO_CONNECT, (uchar) C_CONN_NAME );
	appendChar( (uchar) std::min( name.length(), 250 ) );

	for( int i = 0; i < std::min( name.length(), 250 ); i++ ) {
	        appendChar( (uchar) (name.toLatin1())[i] );
	}
	send();
}
