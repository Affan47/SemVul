WriteSingleQuotedString(ostream& out, const std::string& str)
		{
			out << "'";
			int codePoint;
			for(std::string::const_iterator i = str.begin();
				GetNextCodePointAndAdvance(codePoint, i, str.end());
				)
			{
				if (codePoint == '\n')
					return false;

				if (codePoint == '\'')
					out << "''";
				else
					WriteCodePoint(out, codePoint);
			}
			out << "'";
			return true;
		}
