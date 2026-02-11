get_name(mail::imap &imapAccount, Token t)
{
	if (t == ATOM || t == STRING)
	{
		string nameVal;

		nameVal= t.text;

		if (oneNameOnly)
		{
			if (hiersep.size() > 0)
			{
				size_t p=nameVal.rfind(hiersep[0]);

				if (p != std::string::npos)
					nameVal=nameVal.substr(p);
			}
		}
		else
		{
			if (pfixLength <= nameVal.length())
				nameVal.erase(0, pfixLength);
		}
		char *p=libmail_u_convert_tobuf(nameVal.c_str(),
						unicode_x_imap_modutf7,
						unicode_default_chset(),
						NULL);

		try {
			nameVal=p;
			free(p);
		} catch (...) {
			free(p);
			LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
		}

		if (nameVal.size() == 0 && !oneNameOnly)
		{
			done();
			return;
		}

		mail::imapFolder f(imapAccount, t.text, hiersep, nameVal, -1);

		f.hasMessages(!noSelect);
		f.hasSubFolders(noSelect || hasChildren);
		folderList.push_back(f);
		next_func= &mail::imapLIST::get_xattr_start;
		xattributes.begin();
	}
	else
		error(imapAccount);
}
