bdecode_node bdecode_node::non_owning() const
	{

		if (m_tokens.empty()) return *this;


		return bdecode_node(&m_tokens[0], m_buffer, m_buffer_size, m_token_idx);
	}
