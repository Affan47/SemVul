processLine(imap &imapAccount,
				 std::vector<const char *> &words)
{
	if (words.size() >= 3 && strcmp(words[0], "*") == 0 &&
	    strcasecmp(words[1], "SNAPSHOTEXISTS") == 0)
	{
		restoringSnapshot=true;
		presnapshotExists=exists=newSmapFolder->index.size();
		return true;
	}

	if (words.size() >= 3 && strcmp(words[0], "*") == 0 &&
	    strcasecmp(words[1], "EXISTS") == 0)
	{
		string n(words[2]);
		istringstream i(n);
		i >> exists;

		if (restoringSnapshot && exists > newSmapFolder->index.size())
			newSmapFolder->index.resize(exists);
		return true;
	}

	if (restoringSnapshot)
	{
		imapFOLDERinfo *saveCurrentFolder=
			imapAccount.currentFolder;

		bool rc;

		imapAccount.currentFolder=newSmapFolder;

		try {
			rc=smapHandler::processLine(imapAccount, words);
		} catch (...) {
			imapAccount.currentFolder=saveCurrentFolder;
			throw;
		}
		imapAccount.currentFolder=saveCurrentFolder;
		return rc;
	}

	return smapHandler::processLine(imapAccount, words);
}
