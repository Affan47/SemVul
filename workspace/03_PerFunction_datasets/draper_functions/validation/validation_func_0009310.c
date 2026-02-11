repeat(String &outBuffer, const SubStringRef &inSubString, size_t length,
		size_t passNum, const String &counterVar)
	{
		String::const_iterator itor = inSubString.begin();
		String::const_iterator end = inSubString.begin() + length;

		while (itor != end)
		{
			if (*itor == '@' && !counterVar.empty())
			{
				SubStringRef subString(&inSubString.getOriginalBuffer(), itor + 1);
				if (subString.find(counterVar) == 0)
				{
					char tmp[16];
					sprintf(tmp, "%lu", passNum);
					outBuffer += tmp;
					itor += counterVar.size() + 1;
				}
				else
				{
					outBuffer.push_back(*itor++);
				}
			}
			else
			{
				outBuffer.push_back(*itor++);
			}
		}
	}
