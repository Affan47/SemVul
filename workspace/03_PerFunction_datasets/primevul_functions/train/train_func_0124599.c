void bdecode_node::swap(bdecode_node& n)
	{


		m_tokens.swap(n.m_tokens);
		std::swap(m_root_tokens, n.m_root_tokens);
		std::swap(m_buffer, n.m_buffer);
		std::swap(m_buffer_size, n.m_buffer_size);
		std::swap(m_token_idx, n.m_token_idx);
		std::swap(m_last_index, n.m_last_index);
		std::swap(m_last_token, n.m_last_token);
		std::swap(m_size, n.m_size);
	}
