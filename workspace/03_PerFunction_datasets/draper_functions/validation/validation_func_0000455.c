installed(imap &imapAccount)
{
	vector<string> oldPathWords;
	vector<string> words;

	path2words(oldPath, oldPathWords);

	path2words(path, words);

	vector<string>::iterator b, e;

	string pstr="";

	if (renameFolder)
	{
		b=oldPathWords.begin();
		e=oldPathWords.end();

		while (b != e)
		{
			pstr += " ";
			pstr += imapAccount.quoteSMAP( *b );
			b++;
		}

		pstr += " \"\"";
	}

	b=words.begin();
	e=words.end();

	while (b != e)
	{
		pstr += " ";
		pstr += imapAccount.quoteSMAP( *b );
		b++;
	}

	imapAccount.imapcmd("", (renameFolder ? "RENAME":
				 createDirectory ? "MKDIR":"CREATE")
			    + pstr + "\n");
}
