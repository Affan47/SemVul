Connect()
{
	password_required = false;
	bad_size = false;
	try {
		if( !m_interface.Connect() )
			return (m_connected = false);
	}
	catch( Barry::BadPassword &bp ) {
		password_out_of_tries = bp.out_of_tries();
		password_remaining_tries = bp.remaining_tries();
		password_required = true;
		return (m_connected = false);
	}
	catch( Barry::BadSize &bs ) {
		bad_size_error = std::string("Barry::BadSize caught in Connect: ") + bs.what();
		bad_size = true;
		return (m_connected = false);
	}
	SetStatus(_("Connected"));
	return (m_connected = true);
}
