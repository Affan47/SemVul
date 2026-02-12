int bdecode(char const* start, char const* end, bdecode_node& ret
		, error_code& ec, int* error_pos, int depth_limit, int token_limit)
	{
		ec.clear();
		ret.clear();

		if (end - start > bdecode_token::max_offset)
		{
			if (error_pos) *error_pos = 0;
			ec = bdecode_errors::limit_exceeded;
			return -1;
		}


		int sp = 0;
		stack_frame* stack = TORRENT_ALLOCA(stack_frame, depth_limit);

		char const* const orig_start = start;

		if (start == end)
			TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);

		while (start <= end)
		{
			if (start >= end) TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);

			if (sp >= depth_limit)
				TORRENT_FAIL_BDECODE(bdecode_errors::depth_exceeded);

			--token_limit;
			if (token_limit < 0)
				TORRENT_FAIL_BDECODE(bdecode_errors::limit_exceeded);


			const char t = *start;

			const int current_frame = sp;


			if (current_frame > 0
				&& ret.m_tokens[stack[current_frame-1].token].type == bdecode_token::dict)
			{
				if (stack[current_frame-1].state == 0)
				{


					if (!numeric(t) && t != 'e')
						TORRENT_FAIL_BDECODE(bdecode_errors::expected_digit);
				}
			}

			switch (t)
			{
				case 'd':
					stack[sp++] = ret.m_tokens.size();


					ret.m_tokens.push_back(bdecode_token(start - orig_start
						, bdecode_token::dict));
					++start;
					break;
				case 'l':
					stack[sp++] = ret.m_tokens.size();


					ret.m_tokens.push_back(bdecode_token(start - orig_start
						, bdecode_token::list));
					++start;
					break;
				case 'i':
				{
					char const* int_start = start;
					bdecode_errors::error_code_enum e = bdecode_errors::no_error;

					start = check_integer(start + 1, end, e);
					if (e)
					{


						if (error_pos) *error_pos = start - orig_start;
						error_pos = NULL;
						start = int_start;
						TORRENT_FAIL_BDECODE(e);
					}
					ret.m_tokens.push_back(bdecode_token(int_start - orig_start
						, 1, bdecode_token::integer, 1));
					TORRENT_ASSERT(*start == 'e');


					++start;
					break;
				}
				case 'e':
				{

					if (sp == 0)
						TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);

					if (sp > 0
						&& ret.m_tokens[stack[sp-1].token].type == bdecode_token::dict
						&& stack[sp-1].state == 1)
					{


						TORRENT_FAIL_BDECODE(bdecode_errors::expected_value);
					}


					ret.m_tokens.push_back(bdecode_token(start - orig_start, 1
						, bdecode_token::end));


					int top = stack[sp-1].token;


					if (ret.m_tokens.size() - top > bdecode_token::max_next_item)
						TORRENT_FAIL_BDECODE(bdecode_errors::limit_exceeded);

					ret.m_tokens[top].next_item = ret.m_tokens.size() - top;


					--sp;
					++start;
					break;
				}
				default:
				{


					if (!numeric(t))
						TORRENT_FAIL_BDECODE(bdecode_errors::expected_value);

					boost::int64_t len = t - '0';
					char const* str_start = start;
					++start;
					if (start >= end) TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);
					bdecode_errors::error_code_enum e = bdecode_errors::no_error;
					start = parse_int(start, end, ':', len, e);
					if (e)
						TORRENT_FAIL_BDECODE(e);


					const ptrdiff_t buff_size = end - start - 1;
					if (len > buff_size)
						TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);
					if (len < 0)
						TORRENT_FAIL_BDECODE(bdecode_errors::overflow);


					++start;
					if (start >= end) TORRENT_FAIL_BDECODE(bdecode_errors::unexpected_eof);


					if (start - str_start - 2 > detail::bdecode_token::max_header)
						TORRENT_FAIL_BDECODE(bdecode_errors::limit_exceeded);

					ret.m_tokens.push_back(bdecode_token(str_start - orig_start
						, 1, bdecode_token::string, start - str_start));
					start += len;
					break;
				}
			}

			if (current_frame > 0
				&& ret.m_tokens[stack[current_frame-1].token].type == bdecode_token::dict)
			{

				stack[current_frame-1].state = ~stack[current_frame-1].state;
			}


			if (sp == 0) break;
		}

done:


		while (sp > 0) {
			TORRENT_ASSERT(ec);
			--sp;


			if (ret.m_tokens[stack[sp].token].type == bdecode_token::dict
				&& stack[sp].state == 1)
			{

				ret.m_tokens.push_back(bdecode_token(start - orig_start
					, 2, bdecode_token::dict));
				ret.m_tokens.push_back(bdecode_token(start - orig_start
					, bdecode_token::end));
			}

			int top = stack[sp].token;
			TORRENT_ASSERT(ret.m_tokens.size() - top <= bdecode_token::max_next_item);
			ret.m_tokens[top].next_item = ret.m_tokens.size() - top;
			ret.m_tokens.push_back(bdecode_token(start - orig_start, 1, bdecode_token::end));
		}

		ret.m_tokens.push_back(bdecode_token(start - orig_start, 0
			, bdecode_token::end));

		ret.m_token_idx = 0;
		ret.m_buffer = orig_start;
		ret.m_buffer_size = start - orig_start;
		ret.m_root_tokens = &ret.m_tokens[0];

		return ec ? -1 : 0;
	}
