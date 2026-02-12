static int getLineToStop( const std::string &fulltext){
	int lineNo=1;
	bool inString=false;
	for (unsigned int i=0; i<fulltext.length(); ++i) {

		if (fulltext[i] == '\n') {
			lineNo++;
			continue;
		}

		if (inString && fulltext.compare(i, 2, "\\\"") == 0) {
			i++;
			continue;
		}

		if (fulltext[i] == '"') {
			inString = !inString;
			continue;
		}

		if (!inString && fulltext.compare(i, 2, "//") == 0) {
			i++;
			while (fulltext[i] != '\n' && i<fulltext.length()) i++;
			lineNo++;
			continue;
		}

		if (!inString && fulltext.compare(i, 2, "/*") == 0) {
			i ++;
			if(i<fulltext.length()) {
				i++;
			}
			else {
				continue;
			}

			while (fulltext.compare(i, 2, "*/") != 0 && i<fulltext.length()) {
				if(fulltext[i]=='\n'){
					lineNo++;
				}
				i++;
			}
		}

		if (fulltext[i]== '{') {
			return lineNo;
		}
	}
	return lineNo;
}
}
