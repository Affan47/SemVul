checkSendFolder(mail::folder *postFolder,
				 mail::smtpInfo * &smtpInfoPtr,
				 SpecialFolder::Info *sentFolderInfo,
				 mail::folder *sentFolder,
				 CursesMessage::EncryptionInfo &encryptInfo)
{
	std::string prompt=_("Send message? (Y/N) ");
	std::string prompt2=_("send message? (Y/N) ");

	std::string fromhdr, replytohdr, customhdr;

	saveheaders(fromhdr, replytohdr, customhdr, NULL);

	if (postFolder)
	{
		if (recipients.size() == 0)
		{
			smtpInfoPtr=NULL;
			return archiveSentFolder(sentFolderInfo, sentFolder);
		}

		prompt=_("Mail copies to listed recipients? (Y/N) ");
		prompt2=_("mail copies to listed recipients? (Y/N) ");
	}

	std::vector<mail::address> addresses;

	std::vector<std::string>::iterator ab=recipients.begin(),
		ae=recipients.end();

	while (ab != ae)
		addresses.push_back( mail::address("", *ab++));


	{
		std::vector<mail::address> a;
		size_t dummy;

		mail::address::fromString(fromhdr, a, dummy);

		addresses.insert(addresses.end(), a.begin(), a.end());
	}

	std::vector<GPG::Key_iterator> defaultKeys;

	GPG::gpg.find_public_keys(addresses, defaultKeys);

	std::vector<GPG::Key_iterator>::iterator kb=defaultKeys.begin(),
		ke=defaultKeys.end();

	while (kb != ke)
	{
		encryptInfo.encryptionKeys.push_back( (*kb++)->fingerprint );
	}

	bool rc=CursesMessage::getSendInfo(prompt, prompt2, *smtpInfoPtr,
					   &encryptInfo);


	return rc && archiveSentFolder(sentFolderInfo, sentFolder);
}
