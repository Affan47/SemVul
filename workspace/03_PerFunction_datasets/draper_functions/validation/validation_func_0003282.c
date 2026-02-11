GetValue(int nth)
{
	std::string ret;
	const char *value = 0;

	if( m_attr ) {
		if( b_vformat_attribute_is_single_valued(m_attr) ) {
			if( nth == 0 )
				value = b_vformat_attribute_get_value(m_attr);
		}
		else {
			value = b_vformat_attribute_get_nth_value(m_attr, nth);
		}
	}

	if( value )
		ret = value;

	return ret;
}
