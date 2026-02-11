ExtractString(const wchar_t **data, std::wstring &str)
{
	str = L"";

	while (**data != 0)
	{

		wchar_t next_char = **data;


		if (next_char == L'\\')
		{

			(*data)++;


			switch (**data)
			{
				case L'"': next_char = L'"'; break;
				case L'\\': next_char = L'\\'; break;
				case L'/': next_char = L'/'; break;
				case L'b': next_char = L'\b'; break;
				case L'f': next_char = L'\f'; break;
				case L'n': next_char = L'\n'; break;
				case L'r': next_char = L'\r'; break;
				case L't': next_char = L'\t'; break;
				case L'u':
				{

					if (wcslen(*data) < 5)
						return false;


					next_char = 0;
					for (int i = 0; i < 4; i++)
					{


						(*data)++;

						next_char <<= 4;


						if (**data >= '0' && **data <= '9')
							next_char |= (**data - '0');
						else if (**data >= 'A' && **data <= 'F')
							next_char |= (10 + (**data - 'A'));
						else if (**data >= 'a' && **data <= 'f')
							next_char |= (10 + (**data - 'a'));
						else
						{

							return false;
						}
					}
					break;
				}


				default:
					return false;
			}
		}


		else if (next_char == L'"')
		{
			(*data)++;
			str.reserve();
			return true;
		}


		else if (next_char < L' ' && next_char != L'\t')
		{

			return false;
		}


		str += next_char;


		(*data)++;
	}


	return false;
}
