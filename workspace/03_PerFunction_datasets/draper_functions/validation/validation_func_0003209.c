Encode(const uint8 *data, int inlen, int &outlen, bool &changed)
{
	changed = Realloc(inlen);

	if (m_len == 0) {
		outlen = 0;
		return NULL;
	}


	if ( m_use_diff ) {
		for (int i = 0; i < m_len; i++) {
			m_buff[i] ^= data[i];
			if (m_buff[i]) {
				changed = true;
			}
		}
	} else {
		memcpy(m_buff, data, m_len);
		changed = true;
	}


	uint8 * enc_buff = new uint8[m_len * 3/2 + 1];
	int i = 0, j = 0;
	while ( i != m_len ) {
		uint8 curr_val = m_buff[i];
		int seq_start = i;
		while ( (i != m_len) && (curr_val == m_buff[i]) && ((i - seq_start) < 0xff)) {
			i++;
		}
		if (i - seq_start > 1) {

			enc_buff[j++] = curr_val;
			enc_buff[j++] = curr_val;
			enc_buff[j++] = i - seq_start;
		} else {

			enc_buff[j++] = curr_val;
		}
	}

	outlen = j;


	if ( m_use_diff ) {
		memcpy(m_buff, data, m_len);
	}

	return enc_buff;
}
