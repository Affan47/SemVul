void ContentLine_Analyzer::DoDeliver(int len, const u_char* data)
	{
	seq_delivered_in_lines = seq;

	while ( len > 0 && ! SkipDeliveries() )
		{
		if ( (CR_LF_as_EOL & CR_as_EOL) &&
		     last_char == '\r' && *data == '\n' )
			{


			last_char = *data;
			--len; ++data; ++seq;
			++seq_delivered_in_lines;
			}

		if ( plain_delivery_length > 0 )
			{
			int deliver_plain = min(plain_delivery_length, (int64_t)len);

			last_char = 0;
			plain_delivery_length -= deliver_plain;
			is_plain = 1;

			ForwardStream(deliver_plain, data, IsOrig());

			is_plain = 0;

			data += deliver_plain;
			len -= deliver_plain;
			if ( len == 0 )
				return;
			}

		if ( skip_pending > 0 )
			SkipBytes(skip_pending);


		if ( seq < seq_to_skip )
			{

			int64_t skip_len = seq_to_skip - seq;
			if ( skip_len > len )
				skip_len = len;

			ForwardUndelivered(seq, skip_len, IsOrig());

			len -= skip_len; data += skip_len; seq += skip_len;
			seq_delivered_in_lines += skip_len;
			}

		if ( len <= 0 )
			break;

		int n = DoDeliverOnce(len, data);
		len -= n;
		data += n;
		seq += n;
		}
	}
