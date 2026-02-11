skip_line(istream& inFile, int nLines)
	{
		for (int i = 0; i < nLines; ++i)
			while ( inFile.get() != '\n' && !inFile.eof() );
	}
