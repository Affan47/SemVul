void ContentLine_Analyzer::InitBuffer(int size)
	{
	if ( buf && buf_len >= size )


		return;

	if ( size < 128 )
		size = 128;

	u_char* b = new u_char[size];

	if ( buf )
		{
		if ( offset > 0 )
			memcpy(b, buf, offset);
		delete [] buf;
		}
	else
		{
		offset = 0;
		last_char = 0;
		}

	buf = b;
	buf_len = size;
	}
