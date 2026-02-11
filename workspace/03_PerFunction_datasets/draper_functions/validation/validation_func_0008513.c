processListStatus(const char *message)
{
	if (message[0] != '2')
	{
		newNewsrc.close();
		if (newNewsrcFilename.size() > 0)
			unlink(newNewsrcFilename.c_str());

		if (atoi(message) == 480 ||
		    atoi(message) == 381)
			fail(message);
		else
			success("Connected to server.");
		return;
	}

	response_func= &mail::nntp::LoginTask::processSubscription;
}
