bdecode_node bdecode_node::list_at(int i) const
	{
		TORRENT_ASSERT(type() == list_t);
		TORRENT_ASSERT(i >= 0);


		bdecode_token const* tokens = m_root_tokens;


		int token = m_token_idx + 1;
		int item = 0;


		if (m_last_index <= i && m_last_index != -1)
		{
			token = m_last_token;
			item = m_last_index;
		}

		while (item < i)
		{
			token += tokens[token].next_item;
			++item;


			TORRENT_ASSERT(tokens[token].type != bdecode_token::end);
		}

		m_last_token = token;
		m_last_index = i;

		return bdecode_node(tokens, m_buffer, m_buffer_size, token);
	}
