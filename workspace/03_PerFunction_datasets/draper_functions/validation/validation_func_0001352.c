installed(imap &imapAccount)
{
	imapFOLDERinfo *p=myimap->currentFolder;

	if (p)
	{
		size_t n=p->index.size();

		if (p->exists < n)
		{
			ostringstream o;

			o << "FETCH " << p->exists+1 << "-" << n
			  << " FLAGS UID\n" << flush;

			expectedFetchCount=(n - p->exists)*2;

			imapAccount.imapcmd("", o.str());
			return;
		}
	}

	smapHandler::ok("OK");
	imapAccount.uninstallHandler(this);
}
