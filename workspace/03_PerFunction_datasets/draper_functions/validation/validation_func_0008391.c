cmd_deluser()
{
	userrec *u;
	context;
	if(!cmdinfo.isparam)
	{
		say("Usage: deluser <acctname>");
		return;
	}

	context;
	u = User_user(cmdinfo.tok1);
	if(!u->registered)
	{
		sayf(0,0,"The nick \"%s\" is not registered.",cmdinfo.tok1);
		return;
	}

	if(u->flags & USER_OWNER)
	{
		sayf(0,0,"You are trying to delete the owner's account, which can not be permitted.");
		return;
	}

	context;
	say("The user \"%s\" has been deleted.",u->acctname);

	if(Grufti->send_notice_user_deleted)
		Note_sendnotification("%s has deleted the user \"%s\".",cmdinfo.user->acctname,u->acctname);

	User_removeuser(u);
	context;
	User_resetallpointers();
}
