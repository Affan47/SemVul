untaggedMessage(imap &imapAccount,
					    string msgname)
{
	if (msgname == "MYRIGHTS")
	{
		imapAccount
			.installBackgroundTask(new parseMyRights(folderName,
								 rights));
		return true;
	}

	if (msgname == "LIST")
	{
		imapAccount
			.installBackgroundTask(new listMyRights(folderName,
								rights));
		return true;
	}
	return false;
}
