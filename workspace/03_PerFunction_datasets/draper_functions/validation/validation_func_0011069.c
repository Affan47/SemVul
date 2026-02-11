operator=( const Regexp & r )
{
	if ( this != &r )
	{
		if ( rc && rc->count-- == 0 )
			delete rc;

		rc = r.rc;
		if ( rc )
			rc->count++;

		str = r.str;
		m_szError = r.m_szError;
	}
	return *this;
}
